#include "lotus_phongrenderer3d.hpp"
#include "lotus_phongshader.hpp"

void PhongRenderer3D::flush()
{
	PhongShader::getInstance().bind();
	while (!m_renderQueue.empty())
	{
		const MeshComponent *meshComponent = m_renderQueue.front();
		
		meshComponent->bind();
		PhongShader::getInstance().updateUniforms(meshComponent->getTransform());
		glDrawElements(GL_TRIANGLES, meshComponent->getMesh()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		
		m_renderQueue.pop_front();
	}
}