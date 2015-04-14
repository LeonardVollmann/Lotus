#ifndef LOTUS_SIMPLE_RENDERER
#define LOTUS_SIMPLE_RENDERER

#include "lotus_irenderer.hpp"
#include "../renderables/lotus_renderable.hpp"

#include <deque>

class SimpleRenderer : public IRenderer
{
private:
	std::deque<const Renderable*> m_renderQueue;
public:
	virtual void submit(const Renderable *renderable) override;
	virtual void render() override;
};

#endif