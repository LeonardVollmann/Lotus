#ifndef LOTUS_SIMPLE_RENDERER_3D_HPP_INCLUDED
#define LOTUS_SIMPLE_RENDERER_3D_HPP_INCLUDED

#include "irenderer.hpp"
#include "renderablecomponent.hpp"
#include "shader.hpp"

#include <deque>

namespace lotus { namespace graphics {

	class SimpleRenderer3D : public IRenderer
	{
	protected:
		std::deque<const RenderableComponent<Renderable<Vertex3D>>*> m_renderQueue;
	public:
		virtual void submit(const void *renderableComponent) override;
		virtual void flush() override;
	};

} }

#endif