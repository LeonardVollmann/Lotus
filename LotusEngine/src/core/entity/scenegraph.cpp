#include "scenegraph.hpp"
#include "../../maths/matrix.hpp"

#include <cstring>
#include <iostream>
#include <string>

namespace lotus {

	SceneGraph::SceneGraph(unsigned int capacity)
	{
		allocate(capacity);
	}

	SceneGraph::~SceneGraph()
	{
		delete m_data.data;
	}

	void SceneGraph::allocate(unsigned int capacity)
	{
		InstanceData newData = {};
		newData.capacity = capacity;
		newData.data = new unsigned char[(sizeof(EntityID)
								+ sizeof(maths::mat4f) * 2
								+ sizeof(InstanceID) * 4)
								* capacity];

		newData.entity		= (EntityID*) newData.data;
		newData.local		= (maths::mat4f*) (newData.entity + capacity);
		newData.global		= (maths::mat4f*) (newData.local + capacity);
		newData.parent		= (InstanceID*) (newData.global + capacity);
		newData.firstChild	= (InstanceID*) (newData.parent + capacity);
		newData.nextSibling	= (InstanceID*) (newData.firstChild + capacity);
		newData.prevSibling	= (InstanceID*) (newData.nextSibling + capacity);

		if (m_data.capacity)
		{
			memcpy(newData.entity, m_data.entity, sizeof(EntityID) * m_data.size);
			memcpy(newData.local, m_data.local, sizeof(maths::mat4f) * m_data.size);
			memcpy(newData.global, m_data.global, sizeof(maths::mat4f) * m_data.size);
			memcpy(newData.parent, m_data.parent, sizeof(InstanceID) * m_data.size);
			memcpy(newData.firstChild, m_data.firstChild, sizeof(InstanceID) * m_data.size);
			memcpy(newData.nextSibling, m_data.nextSibling, sizeof(InstanceID) * m_data.size);
			memcpy(newData.prevSibling, m_data.prevSibling, sizeof(InstanceID) * m_data.size);

			newData.size = m_data.size;
			delete m_data.data;
		}

		m_data = newData;
	}

	void SceneGraph::printInstanceData()
	{
		for (InstanceID id = 0; id < m_data.size; id++)
		{
			std::cout << "InstanceID:      " << id << std::endl;
			std::cout << "-- EntityID:     " << idToUnsignedInt(m_data.entity[id]) << std::endl;
			std::cout << "-- Parent:       " << m_data.parent[id] << std::endl;
			std::cout << "-- First Child:  " << m_data.firstChild[id] << std::endl;
			std::cout << "-- Next Sibling: " << m_data.nextSibling[id] << std::endl;
			std::cout << "-- Prev Sibling: " << m_data.prevSibling[id] << std::endl;
			std::cout << std::endl;
		}
	}

	InstanceID SceneGraph::getInstanceID(EntityID entity)
	{

		auto it = m_map.find(entity);
		return it != m_map.end() ? it->second : EMPTY_INSTANCE_ID;
	}

	bool SceneGraph::isValid(InstanceID id)
	{
		return id != EMPTY_INSTANCE_ID;
	}

	void SceneGraph::create(EntityID entity, const maths::mat4f &transform)
	{
		if (m_data.size == m_data.capacity)
		{
			allocate(2 * m_data.capacity); //TODO: Figure out better system for this!
		}

		const unsigned int index = m_data.size;
		m_data.entity[index]		= entity;
		m_data.local[index]			= transform;
		m_data.global[index]		= transform;
		m_data.parent[index]		= EMPTY_INSTANCE_ID;
		m_data.firstChild[index]	= EMPTY_INSTANCE_ID;
		m_data.nextSibling[index]	= EMPTY_INSTANCE_ID;
		m_data.prevSibling[index]	= EMPTY_INSTANCE_ID;
		m_map.insert(std::pair<EntityID, InstanceID>(entity, index));

		m_data.size++;
	}

	void SceneGraph::destroy(EntityID entity)
	{
		InstanceID id = getInstanceID(entity);
		if (isValid(id)) return;
		InstanceID last = m_data.size - 1;

		m_map.erase(entity);
		m_data.local[id] = maths::mat4f(1.0f);
		m_data.global[id] = maths::mat4f(1.0f);

		m_data.entity[id]		= m_data.entity[last];
		m_data.local[id]		= m_data.local[last];
		m_data.global[id]		= m_data.global[last];
		m_data.parent[id]		= m_data.parent[last];
		m_data.firstChild[id]	= m_data.parent[last];
		m_data.nextSibling[id]	= m_data.nextSibling[last];
		m_data.prevSibling[id]	= m_data.prevSibling[last];

		m_map.find(m_data.entity[id])->second = id;

		m_data.size--;
	}

	void SceneGraph::link(InstanceID child, InstanceID parent)
	{
		if (isValid(m_data.parent[child])) unlink(child);

		if (isValid(m_data.firstChild[parent]))
		{
			m_data.nextSibling[child] = m_data.firstChild[parent];
			m_data.prevSibling[m_data.firstChild[parent]] = child;
		}

		m_data.firstChild[parent] = child;
		m_data.parent[child] = parent;
	}

	void SceneGraph::unlink(InstanceID id)
	{
		if (isValid(m_data.prevSibling[id]))
		{
			m_data.nextSibling[m_data.prevSibling[id]] = m_data.nextSibling[id];
		}
		else
		{
			m_data.firstChild[m_data.parent[id]] = m_data.nextSibling[id];
		}

		if (isValid(m_data.nextSibling[id]))
		{
			m_data.prevSibling[m_data.nextSibling[id]] = m_data.prevSibling[id];
		}

		m_data.parent[id] = EMPTY_INSTANCE_ID;
		m_data.nextSibling[id] = EMPTY_INSTANCE_ID;
		m_data.prevSibling[id] = EMPTY_INSTANCE_ID;
	}

	void SceneGraph::setLocalTransform(InstanceID id, const maths::mat4f &transform)
	{
		if (!isValid(m_firstDirty))
		{
			m_firstDirty = m_data.size;
		}

		m_firstDirty--;
		m_data.local[id] = transform;
		swap(id, m_firstDirty);
	}

	void SceneGraph::transformInstance(InstanceID id, const maths::mat4f &transform)
	{
		setLocalTransform(id, transform * m_data.local[id]);
	}

	void SceneGraph::updateGlobalTransforms()
	{
		for (InstanceID id = m_firstDirty; id < m_data.size; id++)
		{
			if (isValid(m_data.parent[id]))
			{
				transformInstance(id, m_data.global[m_data.parent[id]]);
			}

			transformChildren(id);
		}
		m_firstDirty = EMPTY_INSTANCE_ID;
	}

	void SceneGraph::swap(InstanceID id0, InstanceID id1)
	{
		EntityID entity			= m_data.entity[id0];
		maths::mat4f local		= m_data.local[id0];
		maths::mat4f global		= m_data.global[id0];
		InstanceID parent		= m_data.parent[id0];
		InstanceID firstChild	= m_data.firstChild[id0];
		InstanceID nextSibling	= m_data.nextSibling[id0];
		InstanceID prevSibling	= m_data.prevSibling[id0];

		m_data.entity[id0]		= m_data.entity[id1];
		m_data.local[id0]		= m_data.local[id1];
		m_data.global[id0]		= m_data.global[id1];
		m_data.parent[id0]		= m_data.parent[id1];
		m_data.firstChild[id0]	= m_data.firstChild[id1];
		m_data.nextSibling[id0]	= m_data.nextSibling[id1];
		m_data.prevSibling[id0]	= m_data.prevSibling[id1];

		m_data.entity[id1]		= entity;
		m_data.local[id1]		= local;
		m_data.global[id1]		= global;
		m_data.parent[id1]		= parent;
		m_data.firstChild[id1]	= firstChild;
		m_data.nextSibling[id1]	= nextSibling;
		m_data.prevSibling[id1]	= prevSibling;
	}

	void SceneGraph::transformChildren(InstanceID id)
	{
		InstanceID current = m_data.firstChild[id];
		while (isValid(current))
		{
			transformInstance(current, m_data.global[m_data.parent[current]]);
			current = m_data.nextSibling[current];
			transformChildren(current);
		}
	}

}