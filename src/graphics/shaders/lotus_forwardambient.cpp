#include "lotus_forwardambient.hpp"

ForwardAmbient &ForwardAmbient::getInstance()
{
	static ForwardAmbient instance;
	return instance;
}

ForwardAmbient::ForwardAmbient() :
	Shader("forward/ambient"),
	m_ambientLight(0.1f, 0.1f, 0.1f)
{
	addVertexShader(m_fileName);
	addFragmentShader(m_fileName);
	compile();
}

void ForwardAmbient::updateUniforms(const Transform &transform) const
{
	Shader::updateUniforms(transform);
	
	setUniformMat4("mvp_matrix", Layer::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transform.getTransformation());
	
	setUniformVec4("baseColor", Material::CURRENT->getVec4("color"));
	setUniformVec3("ambientLight", m_ambientLight);
}