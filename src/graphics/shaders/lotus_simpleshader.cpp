#include "lotus_simpleshader.hpp"

SimpleShader &SimpleShader::getInstance()
{
	static SimpleShader instance;
	return instance;
}

SimpleShader::SimpleShader() :
	Shader("simple")
{
	addVertexShader(m_fileName);
	addFragmentShader(m_fileName);
	compile();

	addUniform("mvp_matrix");
	addUniform("ml_matrix");

	addUniform("baseColor");
}

void SimpleShader::updateUniforms(const Transform &transform) const
{
	mat4 transformation = transform.getTransformation();
	setUniformMat4("mvp_matrix", Layer::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);

	setUniformVec4("baseColor", Material::CURRENT->getColor());
}