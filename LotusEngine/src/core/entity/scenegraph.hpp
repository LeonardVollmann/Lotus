#pragma once

#include "entity.hpp"
#include "../../maths/types.hpp"

#include <map>

namespace lotus
{

typedef unsigned int InstanceID;
static constexpr InstanceID EMPTY_INSTANCE_ID = (InstanceID)-1;

class SceneGraph
{
private:
	struct InstanceData
	{
		unsigned int size     = 0;
		unsigned int capacity = 0;

		unsigned char *data     = nullptr;
		EntityID *entity        = nullptr;
		maths::mat4f *local     = nullptr;
		maths::mat4f *global    = nullptr;
		InstanceID *parent      = nullptr;
		InstanceID *firstChild  = nullptr;
		InstanceID *nextSibling = nullptr;
		InstanceID *prevSibling = nullptr;
	};

	InstanceData m_data;
	std::map<EntityID, InstanceID> m_map;
	InstanceID m_firstDirty;

public:
	SceneGraph(unsigned int capacity);
	virtual ~SceneGraph();

	void allocate(unsigned int capacity);
	void printInstanceData();

	InstanceID getInstanceID(EntityID entity);
	bool isValid(InstanceID id);

	void create(EntityID entity, const maths::mat4f &transform);
	void destroy(EntityID entity);

	void link(InstanceID child, InstanceID parent);
	void unlink(InstanceID i);

	void setLocalTransform(InstanceID id, const maths::mat4f &transform);
	void transformInstance(InstanceID id, const maths::mat4f &transform);
	void updateGlobalTransforms();

private:
	void swap(InstanceID id0, InstanceID id1);
	void transformChildren(InstanceID id);
};

} // namespace lotus