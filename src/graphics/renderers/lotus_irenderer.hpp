#ifndef LOTUS_I_RENDERER_HPP_INCLUDED
#define LOTUS_I_RENDERER_HPP_INCLUDED

#include <GL/glew.h>

class Renderable;

class IRenderer
{
public:
	virtual ~IRenderer() {}

	virtual void submit(const Renderable *renderable) = 0;
	virtual void render() = 0;
};

#endif