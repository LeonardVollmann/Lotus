#include "lotus_entity.hpp"
#include "lotus_entitycomponent.hpp"

Entity::Entity(const Transform &transform) :
	m_transform(transform) {}

Entity::~Entity()
{
	for (auto it = m_children.begin(); it < m_children.end(); it++)
	{
		delete *it;
	}

	for (auto it = m_components.begin(); it < m_components.end(); it++)
	{
		delete *it;
	}
}

void Entity::update(double delta)
{
	for (auto it = m_children.begin(); it < m_children.end(); it++)
	{
		(*it)->update(delta);
	}

	for (auto it = m_components.begin(); it < m_components.end(); it++)
	{
		(*it)->update(delta);
	}
}

Entity &Entity::addChild(Entity *child)
{
	m_children.push_back(child);
	return *this;
}

Entity &Entity::addComponent(EntityComponent *component)
{
	m_components.push_back(component);
	component->setEntity(this);
	return *this;
}

std::vector<Entity*> Entity::getAllDescendants() const
{
	std::vector<Entity*> result;

	result.push_back(const_cast<Entity*>(this));
	for (auto it = m_children.begin(); it < m_children.end(); it++)
	{
		std::vector<Entity*> descendants = (*it)->getAllDescendants();
		result.insert(result.begin(), descendants.begin(), descendants.end());
	}

	return result;
}

void Entity::submitToRenderer(IRenderer *renderer) const
{
	for (auto it = m_children.begin(); it < m_children.end(); it++)
	{
		(*it)->submitToRenderer(renderer);
	}

	for (auto it = m_components.begin(); it < m_components.end(); it++)
	{
		(*it)->submitToRenderer(renderer);
	}
}