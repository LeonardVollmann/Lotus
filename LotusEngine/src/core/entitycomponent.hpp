#pragma once

#include "../graphics/renderers/irenderer.hpp"

namespace lotus
{

class Entity;

class EntityComponent
{
protected:
	Entity *m_entity;

public:
	virtual ~EntityComponent() {}

	virtual void update(float delta) {}
	virtual void render(graphics::IRenderer *renderer) const {}

	inline Entity *getEntity() const { return m_entity; }
	inline void setEntity(Entity *entity) { m_entity = entity; }
};

} // namespace lotus