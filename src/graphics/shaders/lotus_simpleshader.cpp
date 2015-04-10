#include "lotus_simpleshader.hpp"

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

void SimpleShader::updateUniforms(const Transform &transform, const Material &material, const Camera &camera, const mat4 &projection) const
{
	setUniformMat4("pr_matrix", projection);
	setUniformMat4("vw_matrix", camera.getViewMatrix());
	setUniformMat4("ml_matrix", transform.getTransformation());

	setUniformVec4("baseColor", material.getColor());
}