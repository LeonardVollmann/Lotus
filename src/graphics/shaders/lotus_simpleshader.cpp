#include "lotus_simpleshader.hpp"

SimpleShader &SimpleShader::getInstance()
{
	static SimpleShader instance;
	return instance;
}

SimpleShader::SimpleShader() :
	Shader("simple")
{
	addVertexShader();
	addFragmentShader();
	compile();

	addUniform("pr_matrix");
	addUniform("vw_matrix");
	addUniform("ml_matrix");

	addUniform("baseColor");
}

void SimpleShader::updateUniforms(const Transform &transform) const
{
	setUniformMat4("pr_matrix", Layer::CURRENT->getProjection());
	setUniformMat4("vw_matrix", Camera::CURRENT->getViewMatrix());
	setUniformMat4("ml_matrix", transform.getTransformation());

	setUniformVec4("baseColor", Material::CURRENT->getColor());
}