#include "simplerenderer3d.hpp"
#include "../shaders/shaderfactory.hpp"

namespace lotus { namespace graphics {

	void SimpleRenderer3D::submit(const void *renderableComponent)
	{
		m_renderQueue.push_back((RenderableComponent<Renderable<Vertex3D>>*) renderableComponent);
	}

	void SimpleRenderer3D::flush()
	{
		ShaderFactory::getBasic()->bind();
		while (!m_renderQueue.empty())
		{
			const RenderableComponent<Renderable<Vertex3D>> *renderableComponent = m_renderQueue.front();
			renderableComponent->bind();
			renderableComponent->getMaterial()->bindTexture("diffuse", 0);
			
			ShaderFactory::getBasic()->updateUniforms();
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);

			m_renderQueue.pop_front();
		}
	}

} }