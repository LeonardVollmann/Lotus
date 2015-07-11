#ifndef LOTUS_ENTITY_HPP_INCLUDED
#define LOTUS_ENTITY_HPP_INCLUDED

#include "transform.hpp"
#include "irenderer.hpp"

#include <vector>

namespace lotus {

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
		virtual void render(graphics::IRenderer *renderer) const;
		Entity &addComponent(EntityComponent *component);

		inline Transform &getTransform() { return m_transform; }
		inline const Transform &getTransform()	const { return m_transform; }
	};

}

#endif