#ifndef LOTUS_ENTITY_HPP_INCLUDED
#define LOTUS_ENTITY_HPP_INCLUDED

#include "lotus_transform.hpp"
#include "../graphics/renderers/lotus_irenderer3d.hpp"

#include <vector>

class EntityComponent;

class Entity
{
protected:
	Transform 						m_transform;
	Entity 							*m_parent;
	std::vector<Entity*> 			m_children;
	std::vector<EntityComponent*> 	m_components;
public:
	Entity(const Transform &transform = Transform());
	virtual ~Entity();

	virtual void update(float delta);
	virtual void render(IRenderer3D *renderer) const;
	Entity &addChild(Entity *child);
	Entity &addComponent(EntityComponent *component);
	std::vector<Entity*> getAllDescendants() const;

	inline Transform &getTransform() { return m_transform; }
	inline const Transform &getTransform()	const { return m_transform; }
	inline Entity *getParent()				const { return m_parent; }
};

#endif