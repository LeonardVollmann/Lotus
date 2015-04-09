#ifndef LOTUS_ENTITY_COMPONENT_HPP_INCLUDED
#define LOTUS_ENTITY_COMPONENT_HPP_INCLUDED

#include "lotus_entity.hpp"

namespace lotus {

	class EntityComponent
	{
	protected:
		Entity *m_entity;
	public:
		virtual ~EntityComponent() {}

		virtual void update() = 0;

		inline Transform &getTransform() const { return m_entity->getTransform(); }
	};

}

#endif