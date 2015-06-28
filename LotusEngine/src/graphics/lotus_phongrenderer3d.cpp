#include "lotus_phongrenderer3d.hpp"
#include "lotus_phongshader.hpp"

void PhongRenderer3D::flush()
{
	PhongShader::getInstance().bind();
	while (!m_renderQueue.empty())
	{
		const RenderableComponent<Renderable<Vertex3D>> *renderableComponent = m_renderQueue.front();
		
		renderableComponent->bind();
		renderableComponent->getMaterial()->bindTexture("diffuse", 0);
		
		PhongShader::getInstance().updateUniforms();
		glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		
		m_renderQueue.pop_front();
	}
}