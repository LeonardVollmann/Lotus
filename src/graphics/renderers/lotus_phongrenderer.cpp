#include "lotus_phongrenderer.hpp"
#include "../shaders/lotus_phongshader.hpp"

void PhongRenderer::render()
{
	PhongShader::getInstance().bind();
	while (!m_renderQueue.empty())
	{
		const RenderableComponent *renderableComponent = m_renderQueue.front();
		
		renderableComponent->bind();
		PhongShader::getInstance().updateUniforms(renderableComponent->getTransform());
		glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		
		m_renderQueue.pop_front();
	}
}