#ifndef LOTUS_SIMPLE_RENDERER
#define LOTUS_SIMPLE_RENDERER

#include "lotus_irenderer.hpp"

class SimpleRenderer : public IRenderer
{
public:
	virtual void render(const Renderable &renderable) const override;
};

#endif