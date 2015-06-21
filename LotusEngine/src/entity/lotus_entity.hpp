#ifndef LOTUS_ENTITY_HPP_INCLUDED
#define LOTUS_ENTITY_HPP_INCLUDED

#include "lotus_transform.hpp"
#include "lotus_irenderer.hpp"

#include <vector>

class EntityComponent;

class Entity
{
protected:
	Transform 						m_transform;
	std::vector<EntityComponent*> 	m_components;
public:
	Entity(const Transform &transform = Transform());
	virtual ~Entity();

	virtual void update(float delta);
	virtual void render(IRenderer *renderer) const;
	Entity &addComponent(EntityComponent *component);

	inline Transform &getTransform() { return m_transform; }
	inline const Transform &getTransform()	const { return m_transform; }
};

#endif