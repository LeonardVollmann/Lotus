#ifndef LOTUS_ENTITY_COMPONENT_HPP_INCLUDED
#define LOTUS_ENTITY_COMPONENT_HPP_INCLUDED

#include "entity.hpp"

namespace lotus {

	class EntityComponent
	{
	protected:
		Entity *m_entity;
	public:
		virtual ~EntityComponent() {} 

		virtual void update(float delta) {}
		virtual void render(graphics::IRenderer *renderer) const {}

		inline Transform &getTransform() const { return m_entity->getTransform(); }
		
		inline void setEntity(Entity *entity) { m_entity = entity; }
	};

}

#endif