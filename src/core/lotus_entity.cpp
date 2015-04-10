#include "lotus_entity.hpp"
#include "lotus_entitycomponent.hpp"

Entity::Entity(const Transform &transform) :
	m_transform(transform) {}

Entity::~Entity()
{
	for (auto it = m_nodes.begin(); it < m_nodes.end(); it++)
	{
		delete *it;
	}

	for (auto it = m_components.begin(); it < m_components.end(); it++)
	{
		delete *it;	
	}
}

void Entity::update()
{
	for (auto it = m_nodes.begin(); it < m_nodes.end(); it++)
	{
		(*it)->update();
	}

	for (auto it = m_components.begin(); it < m_components.end(); it++)
	{
		(*it)->update();
	}
}

void Entity::addNode(Entity *node)
{
	m_nodes.push_back(node);
}

void Entity::addComponent(EntityComponent *component)
{
	m_components.push_back(component);
}

std::vector<Entity*> Entity::getAllDescendants() const
{
	std::vector<Entity*> result;

	result.push_back(const_cast<Entity*>(this));
	for (auto it = m_nodes.begin(); it < m_nodes.end(); it++)
	{
		std::vector<Entity*> descendants = (*it)->getAllDescendants();
		result.insert(result.begin(), descendants.begin(), descendants.end());
	}

	return result;
}