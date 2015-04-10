#ifndef LOTUS_ENTITY_HPP_INCLUDED
#define LOTUS_ENTITY_HPP_INCLUDED

#include "lotus_transform.hpp"

#include <vector>

class EntityComponent;

class Entity
{
private:
	Transform 						m_transform;
	Entity 							*m_parent;
	std::vector<Entity*> 			m_nodes;
	std::vector<EntityComponent*> 	m_components;
public:
	Entity(const Transform &transform);
	virtual ~Entity();

	void update();
	void addNode(Entity *node);
	void addComponent(EntityComponent *component);
	std::vector<Entity*> getAllDescendants() const;

	inline Transform &getTransform() { return m_transform; }
	inline Entity *getParent() const { return m_parent; }
};

#endif