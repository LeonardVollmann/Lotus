#ifndef I_RENDERABLE_HPP
#define I_RENDERABLE_HPP

#include "../renderables/renderable.hpp"

#include <GL/glew.h>

namespace lotus { namespace graphics {

	class IRenderer
	{
	public:
		virtual void render(const Renderable &renderable) const = 0;
	};

} }

#endif