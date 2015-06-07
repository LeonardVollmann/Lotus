#ifndef LOTUS_I_RENDERABLE_COMPONENT_HPP_INCLUDED
#define LOTUS_I_RENDERABLE_COMPONENT_HPP_INCLUDED

#include "lotus_entitycomponent.hpp"

class IRenderableComponent : public EntityComponent
{
public:
	virtual void bind() const = 0;
};

#endif