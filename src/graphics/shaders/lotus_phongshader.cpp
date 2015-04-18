#include "lotus_phongshader.hpp"

PhongShader &PhongShader::getInstance()
{
	static PhongShader instance;
	return instance;
}

PhongShader::PhongShader() :
	Shader("phong"),
	m_ambientLight(vec3(0.1f, 0.1f, 0.1f)),
	m_directionalLight(BaseLight(vec3(1.0f, 1.0f, 1.0f), 0.0f), vec3(0.0f, 0.0f, 0.0f))
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
		addUniform(pointLightName + ".range");
	}

	for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		std::string spotLightName = "spotLights[" + std::to_string(i) + "]";

		addUniform(spotLightName + ".pointLight.base.color");
		addUniform(spotLightName + ".pointLight.base.intensity");
		addUniform(spotLightName + ".pointLight.atten.constant");
		addUniform(spotLightName + ".pointLight.atten.linear");
		addUniform(spotLightName + ".pointLight.atten.exponent");
		addUniform(spotLightName + ".pointLight.pos");
		addUniform(spotLightName + ".pointLight.range");
		addUniform(spotLightName + ".direction");
		addUniform(spotLightName + ".cutoff");
	}
}

void PhongShader::updateUniforms(const Transform &transform) const
{
	setUniformMat4("pr_matrix", Layer::CURRENT->getProjection());
	setUniformMat4("vw_matrix", Camera::CURRENT->getViewMatrix());
	setUniformMat4("ml_matrix", transform.getTransformation());

	setUniformVec3("cameraPos", Camera::CURRENT->getTransform().getPos());

	setUniformVec4("baseColor", Material::CURRENT->getColor());
	setUniformFloat("specularIntensity", Material::CURRENT->getSpecularIntensity());
	setUniformFloat("specularPower", Material::CURRENT->getSpecularPower());

	setUniformVec3("ambientLight", m_ambientLight);
	setUniformDirectionalLight("directionalLight", m_directionalLight);

	for (int i = 0; i < m_numPointLights; i++)
	{
		setUniformPointLight("pointLights[" + std::to_string(i) + "]", m_pointLights[i]);
	}

	for (int i = 0; i < m_numSpotLights; i++)
	{
		setUniformSpotLight("spotLights[" + std::to_string(i) + "]", m_spotLights[i]);
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
	setUniformFloat(uniform + ".range", pointLight.range);
}

void PhongShader::setUniformSpotLight(const std::string &uniform, const SpotLight &spotLight) const
{
	setUniformPointLight(uniform + ".pointLight", spotLight.pointLight);
	setUniformVec3(uniform + ".direction", spotLight.direction);
	setUniformFloat(uniform + ".cutoff", spotLight.cutoff);
}

void PhongShader::setPointLights(PointLight *pointLights, int numLights)
{
	if (numLights > MAX_POINT_LIGHTS)
	{
		std::cerr << "ERROR: Too many PointLights." << std::endl;
	}
	else
	{
		m_pointLights = pointLights;
		m_numPointLights = numLights;
	}
}

void PhongShader::setSpotLights(SpotLight *spotLights, int numLights)
{
	if (numLights > MAX_SPOT_LIGHTS)
	{
		std::cerr << "ERROR: Too many SpotLights." << std::endl;
	}
	else
	{
		m_spotLights = spotLights;
		m_numSpotLights = numLights;
	}
}