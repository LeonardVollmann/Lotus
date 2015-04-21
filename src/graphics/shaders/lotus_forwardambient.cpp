#include "lotus_forwardambient.hpp"

ForwardAmbient &ForwardAmbient::getInstance()
{
	static ForwardAmbient instance;
	return instance;
}

ForwardAmbient::ForwardAmbient() :
	Shader("forwardambient"),
	m_ambientLight(0.1f, 0.1f, 0.1f)
{
	addVertexShader();
	addFragmentShader();
	compile();
	
	addUniform("pr_matrix");
	addUniform("vw_matrix");
	addUniform("ml_matrix");
	
	addUniform("baseColor");
	addUniform("ambientLight");
}

void ForwardAmbient::updateUniforms(const Transform &transform) const
{
	setUniformMat4("pr_matrix", Layer::CURRENT->getProjection());
	setUniformMat4("vw_matrix", Camera::CURRENT->getViewMatrix());
	setUniformMat4("ml_matrix", transform.getTransformation());
	
	setUniformVec4("baseColor", Material::CURRENT->getColor());
	setUniformVec3("ambientLight", m_ambientLight);
}