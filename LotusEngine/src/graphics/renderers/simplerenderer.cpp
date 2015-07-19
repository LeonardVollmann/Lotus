#include "simplerenderer.hpp"
#include "../shaders/shaderfactory.hpp"

namespace lotus { namespace graphics {

	template <typename RENDERABLE_T>
	void SimpleRenderer<RENDERABLE_T>::submit(const void *renderableComponent)
	{
		m_renderQueue.push_back((RenderableComponent<RENDERABLE_T>*) renderableComponent);
	}

	template <typename RENDERABLE_T>
	void SimpleRenderer<RENDERABLE_T>::flush()
	{
		ShaderFactory::getBasic()->bind();
		while (!m_renderQueue.empty())
		{
			const RenderableComponent<RENDERABLE_T> *renderableComponent = m_renderQueue.front();
			renderableComponent->bind();
			renderableComponent->getMaterial()->bindTexture("diffuse", 0);
			
			ShaderFactory::getBasic()->updateUniforms();
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);

			m_renderQueue.pop_front();
		}
	}

	template class SimpleRenderer<Renderable<Vertex2D>>;
	template class SimpleRenderer<Renderable<Vertex3D>>;

} }