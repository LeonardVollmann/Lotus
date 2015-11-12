#include "lighting.hpp"
#include "shader.hpp"
#include "../maths/functions.hpp"

#include <string>

namespace lotus { namespace graphics {

	Attenuation::Attenuation(float constant, float linear, float exponent) :
		m_constant(constant),
		m_linear(linear),
		m_exponent(exponent) {}

	Attenuation::Attenuation(const maths::vec3f &attenuation) :
		m_constant(attenuation.x),
		m_linear(attenuation.y),
		m_exponent(attenuation.z) {}

	const AmbientLight *AmbientLight::CURRENT;

	void AmbientLight::getUniformLocations(const ShaderResource *shader, const std::string &name, GLuint *locations)
	{
		locations[0] = glGetUniformLocation(shader->getShaderProgram(), name.c_str());
	}

	void AmbientLight::setUniformValues(const Shader *shader, GLuint *locations)
	{
		shader->setUniform(locations[0], CURRENT->getLight());
	}

	AmbientLight::AmbientLight(const maths::vec3f &light) :
		m_light(light) {}

	AmbientLight::AmbientLight(float r, float g, float b) :
		m_light(r, g, b) {}

	void AmbientLight::bind() const
	{
		CURRENT = this;
	}

	BaseLight::BaseLight() :
		m_color(1.0f, 1.0f, 1.0f),
		m_intensity(1.0f) {}

	BaseLight::BaseLight(const maths::vec3f &color, float intensity) :
		m_color(color),
		m_intensity(intensity) {}

	const DirectionalLight *DirectionalLight::CURRENT;

	void DirectionalLight::getUniformLocations(const ShaderResource *shader, const std::string &name, GLuint *locations)
	{
		locations[0] = glGetUniformLocation(shader->getShaderProgram(), (name + ".base.color").c_str());
		locations[1] = glGetUniformLocation(shader->getShaderProgram(), (name + ".base.intensity").c_str());
		locations[2] = glGetUniformLocation(shader->getShaderProgram(), (name + ".direction").c_str());
	}

	void DirectionalLight::setUniformValues(const Shader *shader, GLuint *locations)
	{
		shader->setUniform(locations[0], CURRENT->getColor());
		shader->setUniform(locations[1], CURRENT->getIntensity());
		shader->setUniform(locations[2], CURRENT->getDirection());
	}

	DirectionalLight::DirectionalLight() :
		BaseLight(),
		m_direction() {}

	DirectionalLight::DirectionalLight(const maths::vec3f &color, float intensity, const maths::vec3f &direction) :
		BaseLight(color, intensity),
		m_direction(direction) {}

	DirectionalLight::DirectionalLight(const maths::vec3f &direction, const BaseLight &base) :
		BaseLight(base),
		m_direction(direction) {}

	void DirectionalLight::bind() const
	{
		CURRENT = this;
	}

	const PointLight *PointLight::CURRENT;

	void PointLight::getUniformLocations(const ShaderResource *shader, const std::string &name, GLuint *locations)
	{
		locations[0] = glGetUniformLocation(shader->getShaderProgram(), (name + ".base.color").c_str());
		locations[1] = glGetUniformLocation(shader->getShaderProgram(), (name + ".base.intensity").c_str());
		locations[2] = glGetUniformLocation(shader->getShaderProgram(), (name + ".atten.constant").c_str());
		locations[3] = glGetUniformLocation(shader->getShaderProgram(), (name + ".atten.linear").c_str());
		locations[4] = glGetUniformLocation(shader->getShaderProgram(), (name + ".atten.exponent").c_str());
		locations[5] = glGetUniformLocation(shader->getShaderProgram(), (name + ".pos").c_str());
		locations[6] = glGetUniformLocation(shader->getShaderProgram(), (name + ".range").c_str());
	}

	void PointLight::setUniformValues(const Shader *shader, GLuint *locations)
	{
		shader->setUniform(locations[0], CURRENT->getColor());
		shader->setUniform(locations[1], CURRENT->getIntensity());
		shader->setUniform(locations[2], CURRENT->getAttenuation().getConstant());
		shader->setUniform(locations[3], CURRENT->getAttenuation().getLinear());
		shader->setUniform(locations[4], CURRENT->getAttenuation().getExponent());
		shader->setUniform(locations[5], CURRENT->getPos());
		shader->setUniform(locations[6], CURRENT->getRange());
	}

	PointLight::PointLight() :
		BaseLight(),
		m_atten(0.0f, 0.0f, 1.0f),
		m_pos(0.0f, 0.0f, 0.0f),
		m_range(calcRange(*this)) {}

	PointLight::PointLight(const maths::vec3f &color, float intensity, const Attenuation &atten, const maths::vec3f &pos) :
		BaseLight(color, intensity),
		m_atten(atten),
		m_pos(pos),
		m_range(calcRange(*this)) {}

	PointLight::PointLight(const Attenuation &atten, const maths::vec3f &pos, const BaseLight &base) :
		BaseLight(base),
		m_atten(atten),
		m_pos(pos),
		m_range(calcRange(*this)) {}

	void PointLight::bind() const
	{
		CURRENT = this;
	}

	float PointLight::calcRange(const PointLight &pointLight)
	{
		float maxColorValue = pointLight.getColor().x > pointLight.getColor().y ? pointLight.getColor().x : pointLight.getColor().y;
		if (pointLight.getColor().z > maxColorValue) maxColorValue = pointLight.getColor().z;

		float a = pointLight.getAttenuation().getExponent();
		float b = pointLight.getAttenuation().getLinear();
		float c = pointLight.getAttenuation().getConstant() - COLOR_DEPTH * pointLight.getIntensity() * maxColorValue;

		return (-b + maths::sqrt<float>(b * b - 4 * a * c)) / (2 * a);
	}

	const SpotLight *SpotLight::CURRENT;

	void SpotLight::getUniformLocations(const ShaderResource *shader, const std::string &name, GLuint *locations)
	{
		locations[0] = glGetUniformLocation(shader->getShaderProgram(), (name + ".pointLight.base.color").c_str());
		locations[1] = glGetUniformLocation(shader->getShaderProgram(), (name + ".pointLight.base.intensity").c_str());
		locations[2] = glGetUniformLocation(shader->getShaderProgram(), (name + ".pointLight.atten.constant").c_str());
		locations[3] = glGetUniformLocation(shader->getShaderProgram(), (name + ".pointLight.atten.linear").c_str());
		locations[4] = glGetUniformLocation(shader->getShaderProgram(), (name + ".pointLight.atten.exponent").c_str());
		locations[5] = glGetUniformLocation(shader->getShaderProgram(), (name + ".pointLight.pos").c_str());
		locations[6] = glGetUniformLocation(shader->getShaderProgram(), (name + ".pointLight.range").c_str());
		locations[7] = glGetUniformLocation(shader->getShaderProgram(), (name + ".direction").c_str());
		locations[8] = glGetUniformLocation(shader->getShaderProgram(), (name + ".cutoff").c_str());
	}

	void SpotLight::setUniformValues(const Shader *shader, GLuint *locations)
	{
		shader->setUniform(locations[0], CURRENT->getColor());
		shader->setUniform(locations[1], CURRENT->getIntensity());
		shader->setUniform(locations[2], CURRENT->getAttenuation().getConstant());
		shader->setUniform(locations[3], CURRENT->getAttenuation().getLinear());
		shader->setUniform(locations[4], CURRENT->getAttenuation().getExponent());
		shader->setUniform(locations[5], CURRENT->getPos());
		shader->setUniform(locations[6], CURRENT->getRange());
		shader->setUniform(locations[7], CURRENT->getDirection());
		shader->setUniform(locations[8], CURRENT->getCutoff());
	}

	SpotLight::SpotLight() :
		PointLight(),
		m_direction(),
		m_cutoff(0.7f) {}

	SpotLight::SpotLight(const maths::vec3f &color, float intensity, const Attenuation &atten, const maths::vec3f &pos, const maths::vec3f &direction, float cutoff) :
		PointLight(color, intensity, atten, pos),
		m_direction(direction),
		m_cutoff(cutoff) {}

	SpotLight::SpotLight(const maths::vec3f &direction, float cutoff, const PointLight &pointLight) :
		PointLight(pointLight),
		m_direction(direction),
		m_cutoff(cutoff) {}

	void SpotLight::bind() const
	{
		CURRENT = this;
	}

} }
