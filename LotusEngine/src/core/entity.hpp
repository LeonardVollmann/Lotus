#pragma once

#include "entitycomponent.hpp"
#include "transform.hpp"
#include "../graphics/renderers/irenderer.hpp"

#include <vector>

namespace lotus
{

class Entity
{
protected:
	Entity *m_parent;
	Transform m_transform;
	std::vector<Entity *> m_children;
	std::vector<EntityComponent *> m_components;

public:
	Entity(const Transform &transform = Transform());
	virtual ~Entity();

	Entity &addChild(Entity *child);
	Entity &addComponent(EntityComponent *component);

	template <typename CHILD_T, typename... ARGS>
	inline Entity &addChild(ARGS &&... args)
	{
		static_assert(std::is_base_of<Entity, CHILD_T>(),
		              "ERROR: Children of Entity have to be subclasses of Entity.\n");
		CHILD_T *child = new CHILD_T(std::forward<ARGS>(args)...);

		return addChild(child);
	}

	template <typename COMPONENT_T, typename... ARGS>
	inline Entity &addComponent(ARGS &&... args)
	{
		static_assert(std::is_base_of<EntityComponent, COMPONENT_T>(),
		              "ERROR: Components have to be subclasses of EntityComponent.\n");
		COMPONENT_T *component = new COMPONENT_T(std::forward<ARGS>(args)...);

		return addComponent(component);
	}

	virtual void update(float delta);
	virtual void render(graphics::IRenderer *renderer) const;

	void setParent(Entity *parent);

	inline Transform &getTransform() { return m_transform; }
	inline const Transform &getTransform() const { return m_transform; }
	inline Entity *getParent() const { return m_parent; }
};

} // namespace lotus