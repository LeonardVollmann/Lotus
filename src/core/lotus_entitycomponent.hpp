#ifndef LOTUS_ENTITY_COMPONENT_HPP_INCLUDED
#define LOTUS_ENTITY_COMPONENT_HPP_INCLUDED

#include "lotus_entity.hpp"

class EntityComponent
{
protected:
	Entity *m_entity;
public:
	virtual void update(float delta) {}
	virtual void render(IRenderer *renderer) const {}

	inline Transform &getTransform() const { return m_entity->getTransform(); }
	
	inline void setEntity(Entity *entity) { m_entity = entity; }
};

#endif