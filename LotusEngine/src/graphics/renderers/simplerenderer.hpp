#ifndef LOTUS_SIMPLE_RENDERER_HPP_INCLUDED
#define LOTUS_SIMPLE_RENDERER_HPP_INCLUDED

#include "irenderer.hpp"
#include "../shader.hpp"
#include "../../core/profiling.hpp"
#include "../../components/renderablecomponent.hpp"

#include <deque>

namespace lotus { namespace graphics {

	template <typename RENDERABLE_T>
	class SimpleRenderer : public IRenderer
	{
	public:
		SimpleRenderer();

		virtual void submit(const void *renderableComponent) override;
		virtual void flush() override;
	protected:
		std::deque<const RenderableComponent<RENDERABLE_T>*>	m_renderQueue;
		Shader													m_shader;
		ProfileTimer											m_renderTimer;
	};

	typedef SimpleRenderer<Renderable<Vertex2D>> SimpleRenderer2D;
	typedef SimpleRenderer<Renderable<Vertex3D>> SimpleRenderer3D;

} }

#endif
