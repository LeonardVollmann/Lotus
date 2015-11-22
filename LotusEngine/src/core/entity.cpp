#include "entity.hpp"
#include "entitycomponent.hpp"

namespace lotus
{

Entity::Entity(const Transform &transform)
: m_transform(transform)
{
}

Entity::~Entity()
{
	for (auto it = m_children.begin(); it != m_children.end(); it++)
	{
		delete *it;
	}

	for (auto it = m_components.begin(); it != m_components.end(); it++)
	{
		delete *it;
	}
}

Entity &Entity::addChild(Entity *child)
{
	child->setParent(this);
	m_children.push_back(child);

	return *this;
}

Entity &Entity::addComponent(EntityComponent *component)
{
	component->setEntity(this);
	m_components.push_back(component);

	return *this;
}

void Entity::update(float delta)
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

void Entity::render(graphics::IRenderer *renderer) const
{
	for (auto it = m_children.begin(); it < m_children.end(); it++)
	{
		(*it)->render(renderer);
	}

	for (auto it = m_components.begin(); it < m_components.end(); it++)
	{
		(*it)->render(renderer);
	}
}

void Entity::setParent(Entity *parent)
{
	m_parent = parent;
	m_transform.setParent(&m_parent->getTransform());
}

} // namespace lotus