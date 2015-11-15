#ifndef LOTUS_SCENE_GRAPH_HPP_INCLUDED
#define LOTUS_SCENE_GRAPH_HPP_INCLUDED

#include "entity.hpp"
#include "../../maths/types.hpp"

#include <map>

namespace lotus {

	typedef unsigned int InstanceID;
	static constexpr InstanceID EMPTY_INSTANCE_ID = (InstanceID) -1;

	class SceneGraph
	{
	public:
		SceneGraph(unsigned int capacity);
		virtual ~SceneGraph();

		void allocate(unsigned int capacity);
		void printInstanceData();

		InstanceID getInstanceID(EntityID entity);
		bool isValid(InstanceID id);

		void create(EntityID entity, const maths::mat4f &transformation);
		void destroy(EntityID entity);

		void link(InstanceID child, InstanceID parent);
		void unlink(InstanceID i);
	private:
		struct InstanceData
		{
			unsigned int size		= 0;
			unsigned int capacity	= 0;

			unsigned char *data		= nullptr;
			EntityID *entity		= nullptr;
			maths::mat4f *local		= nullptr;
			maths::mat4f *world		= nullptr;
			InstanceID *parent		= nullptr;
			InstanceID *firstChild	= nullptr;
			InstanceID *nextSibling	= nullptr;
			InstanceID *prevSibling	= nullptr;
		};

		InstanceData m_data;
		std::map<EntityID, InstanceID> m_map;
	};

}

#endif