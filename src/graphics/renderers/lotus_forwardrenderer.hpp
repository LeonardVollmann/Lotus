#ifndef LOTUS_FORWARD_RENDERER_HPP_INCLUDED
#define LOTUS_FORWARD_RENDERER_HPP_INCLUDED

#include "lotus_simplerenderer.hpp"

class ForwardRenderer : public SimpleRenderer
{
public:
	virtual void flush() override;
};

#endif