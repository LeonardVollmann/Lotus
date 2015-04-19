#include "lotus_simplerenderer.hpp"

void SimpleRenderer::submit(const RenderableComponent *renderableComponent)
{
	m_renderQueue.push_back(renderableComponent);
}

void SimpleRenderer::render(Shader *shader)
{
	shader->bind();
	while (!m_renderQueue.empty())
	{
		const RenderableComponent *renderableComponent = m_renderQueue.front();
		
		renderableComponent->bind();
		shader->updateUniforms(renderableComponent->getTransform());
		glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);

		m_renderQueue.pop_front();
	}
}