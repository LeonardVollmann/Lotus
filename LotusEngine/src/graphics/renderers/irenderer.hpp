#ifndef LOTUS_I_RENDERER_HPP_INCLUDED
#define LOTUS_I_RENDERER_HPP_INCLUDED

#include <GL/glew.h>

namespace lotus { namespace graphics {

	class IRenderer
	{
	public:
		virtual ~IRenderer() {}

		virtual void prepare() {}
		virtual void submit(const void *renderableComponent) = 0;
		virtual void flush() = 0;
		
		virtual void displayProfilingInfo() {}
	};

} }

#endif
