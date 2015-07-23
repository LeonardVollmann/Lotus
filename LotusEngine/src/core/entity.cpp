#include "entity.hpp"
#include "entitycomponent.hpp"

namespace lotus {

	Entity::Entity(const Transform &transform) :
		m_transform(transform) {}


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

}
