#include "lotus_simplerenderer.hpp"
#include "../shaders/lotus_simpleshader.hpp"

void SimpleRenderer::submit(const RenderableComponent *renderableComponent)
{
	m_renderQueue.push_back(renderableComponent);
}

void SimpleRenderer::flush()
{
	SimpleShader::getInstance().bind();
	while (!m_renderQueue.empty())
	{
		const RenderableComponent *renderableComponent = m_renderQueue.front();
		
		renderableComponent->bind();
		SimpleShader::getInstance().updateUniforms(renderableComponent->getTransform());
		glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);

		m_renderQueue.pop_front();
	}
}