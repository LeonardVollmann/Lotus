#ifndef SIMPLE_RENDERER
#define SIMPLE_RENDERER

#include "irenderer.hpp"
#include "../renderables/renderable2d.hpp"

namespace lotus { namespace graphics {

	class SimpleRenderer : public IRenderer
	{
	public:
		virtual void render(const Renderable &renderable) const override;
	};

} }

#endif