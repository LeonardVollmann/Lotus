#include "lotus_simplerenderer3d.hpp"
#include "lotus_simpleshader.hpp"

void SimpleRenderer3D::submit(const IRenderableComponent *meshComponent)
{
	m_renderQueue.push_back((MeshComponent*) meshComponent);
}

void SimpleRenderer3D::flush()
{
	SimpleShader::getInstance().bind();
	while (!m_renderQueue.empty())
	{
		const MeshComponent *meshComponent = m_renderQueue.front();
		meshComponent->bind();
		
		SimpleShader::getInstance().updateUniforms(meshComponent->getTransform());
		glDrawElements(GL_TRIANGLES, meshComponent->getMesh()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);

		m_renderQueue.pop_front();
	}
}