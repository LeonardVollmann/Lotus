#ifndef LOTUS_I_RENDERER_HPP_INCLUDED
#define LOTUS_I_RENDERER_HPP_INCLUDED

#include <GL/glew.h>

class Renderable;
class Shader;

class IRenderer
{
public:
	virtual ~IRenderer() {}

	virtual void submit(const Renderable *renderable) = 0;
	virtual void render(Shader *shader) = 0;
};

#endif