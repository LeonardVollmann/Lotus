#ifndef LOTUS_I_RENDERER_HPP_INCLUDED
#define LOTUS_I_RENDERER_HPP_INCLUDED

#include <GL/glew.h>

class IRenderer
{
public:
	virtual ~IRenderer() {}
	
	virtual void submit(const void *renderableComponent) = 0;
	virtual void flush() = 0;
};

#endif