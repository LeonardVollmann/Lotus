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

void SimpleShader::updateUniforms() const
{
	Shader::updateUniforms();
	
	mat4 transformation = Transform::CURRENT->getTransformation();
	setUniformMat4("mvp_matrix", Scene::CURRENT->getProjection() * Camera::CURRENT->getViewMatrix() * transformation);
	setUniformMat4("ml_matrix", transformation);

	setUniformVec4("baseColor", *Material::CURRENT->getVec4("color"));
}