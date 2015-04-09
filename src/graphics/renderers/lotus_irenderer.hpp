#ifndef LOTUS_I_RENDERER_HPP_INCLUDED
#define LOTUS_I_RENDERER_HPP_INCLUDED

#include "../renderables/lotus_renderable.hpp"

#include <GL/glew.h>

namespace lotus { namespace graphics {

	class IRenderer
	{
	public:
		virtual void render(const Renderable &renderable) const = 0;
	};

} }

#endif