#ifndef LOTUS_SIMPLE_RENDERER_HPP_INCLUDED
#define LOTUS_SIMPLE_RENDERER_HPP_INCLUDED

#include "irenderer.hpp"
#include "../shader.hpp"
#include "../../components/renderablecomponent.hpp"

#include <deque>

namespace lotus { namespace graphics {

	template <typename RENDERABLE_T>
	class SimpleRenderer : public IRenderer
	{
	protected:
		std::deque<const RenderableComponent<RENDERABLE_T>*>	m_renderQueue;
		Shader													m_shader;
	public:
		SimpleRenderer();

		virtual void submit(const void *renderableComponent) override;
		virtual void flush() override;
	};

	typedef SimpleRenderer<Renderable<Vertex2D>> SimpleRenderer2D;
	typedef SimpleRenderer<Renderable<Vertex3D>> SimpleRenderer3D;

} }

#endif