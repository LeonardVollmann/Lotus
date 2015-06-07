#ifndef LOTUS_I_RENDERER_HPP_INCLUDED
#define LOTUS_I_RENDERER_HPP_INCLUDED

#include <GL/glew.h>

class IRenderableComponent;

class IRenderer
{
public:
	virtual ~IRenderer() {}
	
	virtual void submit(const IRenderableComponent *mesh) = 0;
	virtual void flush() = 0;
};

#endif