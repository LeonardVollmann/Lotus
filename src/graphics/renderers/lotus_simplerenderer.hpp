#ifndef LOTUS_SIMPLE_RENDERER
#define LOTUS_SIMPLE_RENDERER

#include "lotus_irenderer.hpp"
#include "../renderables/lotus_renderable2d.hpp"

namespace lotus { namespace graphics {

	class SimpleRenderer : public IRenderer
	{
	public:
		virtual void render(const Renderable &renderable) const override;
	};

} }

#endif