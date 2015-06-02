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
}

void SimpleShader::updateUniforms(const Transform &transform) const
{
	Shader::updateUniforms(transform);
	
	mat4 transformation = transform.getTransformation();
	setUniformMat4("mvp_matrix", Layer::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);

	setUniformVec4("baseColor", Material::CURRENT->getVec4("color"));
}