#ifndef LOTUS_SIMPLE_RENDERER
#define LOTUS_SIMPLE_RENDERER

#include "lotus_irenderer.hpp"
#include "../shaders/lotus_shader.hpp"
#include "../../components/lotus_renderablecomponent.hpp"

#include <deque>

class SimpleRenderer : public IRenderer
{
protected:
	std::deque<const RenderableComponent*> m_renderQueue;
public:
	virtual void submit(const RenderableComponent *renderable) override;
	virtual void flush() override;
};

#endif