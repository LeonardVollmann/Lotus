#include "entity.hpp"
#include "entitycomponent.hpp"

namespace lotus {

	Entity::Entity(const Transform &transform) :
		m_transform(transform) {}

	Entity::~Entity()
	{
		for (auto it = m_components.begin(); it < m_components.end(); it++)
		{
			delete *it;
		}
	}

	void Entity::update(float delta)
	{
		for (auto it = m_components.begin(); it < m_components.end(); it++)
		{
			(*it)->update(delta);
		}
	}

	void Entity::render(graphics::IRenderer *renderer) const
	{
		for (auto it = m_components.begin(); it < m_components.end(); it++)
		{
			(*it)->render(renderer);
		}
	}

	Entity &Entity::addComponent(EntityComponent *component)
	{
		m_components.push_back(component);
		component->setEntity(this);
		return *this;
	}

}