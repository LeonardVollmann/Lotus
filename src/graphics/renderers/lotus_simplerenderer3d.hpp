#ifndef LOTUS_SIMPLE_RENDERER_3D_HPP_INCLUDED
#define LOTUS_SIMPLE_RENDERER_3D_HPP_INCLUDED

#include "lotus_irenderer3d.hpp"
#include "../shaders/lotus_shader.hpp"
#include "../../components/lotus_meshcomponent.hpp"

#include <deque>

class SimpleRenderer3D : public IRenderer3D
{
protected:
	std::deque<const MeshComponent*> m_renderQueue;
public:
	virtual void submit(const MeshComponent *meshComponent) override;
	virtual void flush() override;
};

#endif