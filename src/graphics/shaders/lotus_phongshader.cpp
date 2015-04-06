#include "lotus_phongshader.hpp"

namespace lotus { namespace graphics { 

	PhongShader::PhongShader() :
		Shader("phong"),
		m_ambientLight(maths::vec3(0.2f, 0.2f, 0.2f)),
		m_directionalLight(BaseLight(maths::vec3(1.0f, 1.0f, 1.0f), 0.0f), maths::vec3(0.0f, 0.0f, 0.0f))
	{
		addVertexShader();
		addFragmentShader();
		compile();

		addUniform("pr_matrix");
		addUniform("vw_matrix");
		addUniform("ml_matrix");

		addUniform("cameraPos");

		addUniform("baseColor");
		addUniform("specularIntensity");
		addUniform("specularPower");

		addUniform("ambientLight");
		addUniform("directionalLight.base.color");
		addUniform("directionalLight.base.intensity");
		addUniform("directionalLight.direction");
	}

	void PhongShader::updateUniforms(const Transform &transform, const Material &material, const Camera &camera, const maths::mat4 &projection) const
	{
		setUniformMat4("pr_matrix", projection);
		setUniformMat4("vw_matrix", camera.getViewMatrix());
		setUniformMat4("ml_matrix", transform.getTransformation());

		setUniformVec3("cameraPos", camera.getTransform().getPos());

		setUniformVec4("baseColor", material.getColor());
		setUniformFloat("specularIntensity", material.getSpecularIntensity());
		setUniformFloat("specularPower", material.getSpecularPower());

		setUniformVec3("ambientLight", m_ambientLight);
		setUniformDirectionalLight("directionalLight", m_directionalLight);
	}


	void PhongShader::setUniformBaseLight(const std::string &uniform, const BaseLight &baseLight) const
	{
		glUniform3f(m_uniforms[uniform + ".color"], baseLight.color.x, baseLight.color.y, baseLight.color.z);
		glUniform1f(m_uniforms[uniform + ".intensity"], baseLight.intensity);
	} 

	void PhongShader::setUniformDirectionalLight(const std::string &uniform, const DirectionalLight &directionalLight) const
	{
		setUniformBaseLight(uniform + ".base", directionalLight.base);
		glUniform3f(m_uniforms[uniform + ".direction"], directionalLight.direction.x, directionalLight.direction.y, directionalLight.direction.z);
	}

	// void Shader::setUniformAttenuation(const std::string &uniform, const Attenuation &attenuation) const
	// {
	// 	setUniformFloat(uniform + ".constant", attenuation.constant);
	// 	setUniformFloat(uniform + ".linear", attenuation.linear);
	// 	setUniformFloat(uniform + ".exponent", attenuation.exponent);
	// }

	// void Shader::setUniformPointLight(const std::string &uniform, const PointLight &pointLight) const
	// {
	// 	setUniformBaseLight(uniform + ".base", pointLight.base);
	// 	setUniformAttenuation(uniform + ".attenuation", pointLight.attenuation);
	// 	setUniformVec3(uniform + ".pos", pointLight.pos);
	// }

} }