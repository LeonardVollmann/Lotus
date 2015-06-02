#ifndef LOTUS_I_RENDERER_3D_HPP_INCLUDED
#define LOTUS_I_RENDERER_3D_HPP_INCLUDED

#include <GL/glew.h>

class MeshComponent;

class IRenderer3D
{
public:
	virtual ~IRenderer3D() {}
	
	virtual void submit(const MeshComponent *mesh) = 0;
	virtual void flush() = 0;
};

#endif