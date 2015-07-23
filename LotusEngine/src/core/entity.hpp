#ifndef LOTUS_ENTITY_HPP_INCLUDED
#define LOTUS_ENTITY_HPP_INCLUDED

#include "entitycomponent.hpp"
#include "transform.hpp"
#include "../graphics/renderers/irenderer.hpp"

#include <vector>
#include <memory>
#include <type_traits>

namespace lotus {

	class Entity
	{
	protected:
		Transform 										m_transform;
		std::vector<std::unique_ptr<Entity>>			m_children;
		std::vector<std::unique_ptr<EntityComponent>> 	m_components;
	public:
		Entity(const Transform &transform = Transform());
		virtual ~Entity() {}

		template <typename CHILD_T, typename... ARGS>
		inline Entity &addChild(ARGS&&... args)
		{
			static_assert(std::is_base_of<Entity, CHILD_T>(), "ERROR: Children of Entity have to be subclasses of Entity.\n");

			CHILD_T *child = new CHILD_T(std::forward<ARGS>(args)...);
			child->setParent(this);

			m_children.push_back(std::unique_ptr<CHILD_T>(child));
			return *this;
		}

		template <typename COMPONENT_T, typename... ARGS>
		inline Entity &addComponent(ARGS&&... args)
		{
			static_assert(std::is_base_of<EntityComponent, COMPONENT_T>(), "ERROR: Components have to be subclasses of EntityComponent.\n");

			COMPONENT_T *component = new COMPONENT_T(std::forward<ARGS>(args)...);
			component->setEntity(this);

			m_components.push_back(std::unique_ptr<COMPONENT_T>(component));
			return *this;
		}

		virtual void update(float delta);
		virtual void render(graphics::IRenderer *renderer) const;

		inline Transform &getTransform() { return m_transform; }
		inline const Transform &getTransform()	const { return m_transform; }
	};

}

#endif
