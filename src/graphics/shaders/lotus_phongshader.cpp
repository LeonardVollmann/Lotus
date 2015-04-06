#include "lotus_phongshader.hpp"

namespace lotus { namespace graphics { 

	PhongShader::PhongShader() :
		Shader("phong"),
		m_ambientLight(maths::vec3(0.1f, 0.1f, 0.1f)),
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

		for (int i = 0; i < MAX_POINT_LIGHTS; i++)
		{
			std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

			addUniform(pointLightName + ".base.color");
			addUniform(pointLightName + ".base.intensity");
			addUniform(pointLightName + ".atten.constant");
			addUniform(pointLightName + ".atten.linear");
			addUniform(pointLightName + ".atten.exponent");
			addUniform(pointLightName + ".pos");
		}
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

		for (int i = 0; i < m_numPointLights; i++)
		{
			setUniformPointLight("pointLights[" + std::to_string(i) + "]", m_pointLights[i]);
		}
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

	void PhongShader::setUniformAttenuation(const std::string &uniform, const Attenuation &attenuation) const
	{
		setUniformFloat(uniform + ".constant", attenuation.constant);
		setUniformFloat(uniform + ".linear", attenuation.linear);
		setUniformFloat(uniform + ".exponent", attenuation.exponent);
	}

	void PhongShader::setUniformPointLight(const std::string &uniform, const PointLight &pointLight) const
	{
		setUniformBaseLight(uniform + ".base", pointLight.base);
		setUniformAttenuation(uniform + ".atten", pointLight.atten);
		setUniformVec3(uniform + ".pos", pointLight.pos);
	}

	void PhongShader::setPointLights(PointLight *pointLights, int numLights)
	{
		if (numLights > MAX_POINT_LIGHTS)
		{
			std::cerr<< "ERROR: Too many PointLights." << std::endl;
		}
		else
		{
			m_pointLights = pointLights;
			m_numPointLights = numLights;
		}
	}

} }