#include "simplerenderer.hpp"
#include "../window.hpp"

namespace lotus { namespace graphics {

	template <typename RENDERABLE_T>
	SimpleRenderer<RENDERABLE_T>::SimpleRenderer() :
		m_shader("basic"),
		m_renderTimer("SimpleRenderer Render Time") {}

	template <typename RENDERABLE_T>
	void SimpleRenderer<RENDERABLE_T>::submit(const void *renderableComponent)
	{
		m_renderQueue.push_back((RenderableComponent<RENDERABLE_T>*) renderableComponent);
	}

	template <typename RENDERABLE_T>
	void SimpleRenderer<RENDERABLE_T>::flush()
	{
		m_renderTimer.start();

		Window::CURRENT->bindAsRenderTarget();
		m_shader.bind();
		while (!m_renderQueue.empty())
		{
			const RenderableComponent<RENDERABLE_T> *renderableComponent = m_renderQueue.front();
			renderableComponent->bind();
			renderableComponent->getMaterial()->bindTexture("diffuse", 0);
			
			m_shader.updateUniforms();
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);

			m_renderQueue.pop_front();
		}
		m_renderTimer.stop();
	}

	template class SimpleRenderer<Renderable<Vertex2D>>;
	template class SimpleRenderer<Renderable<Vertex3D>>;

} }
