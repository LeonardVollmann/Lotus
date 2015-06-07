#ifndef LOTUS_SIMPLE_RENDERER_3D_HPP_INCLUDED
#define LOTUS_SIMPLE_RENDERER_3D_HPP_INCLUDED

#include "lotus_irenderer.hpp"
#include "lotus_shader.hpp"
#include "lotus_meshcomponent.hpp"

#include <deque>

class SimpleRenderer3D : public IRenderer
{
protected:
	std::deque<const MeshComponent*> m_renderQueue;
public:
	virtual void submit(const IRenderableComponent *meshComponent) override;
	virtual void flush() override;
};

#endif