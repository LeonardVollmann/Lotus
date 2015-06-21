#include "lotus_lighting.hpp"

#include <cmath>

Attenuation::Attenuation(float constant, float linear, float exponent) :
	m_constant(constant),
	m_linear(linear),
	m_exponent(exponent) {}

Attenuation::Attenuation(const vec3 &attenuation) :
	m_constant(attenuation.x),
	m_linear(attenuation.y),
	m_exponent(attenuation.z) {}

BaseLight::BaseLight() :
	m_color(1.0f, 1.0f, 1.0f),
	m_intensity(1.0f) {}

BaseLight::BaseLight(const vec3 &color, float intensity) :
	m_color(color),
	m_intensity(intensity) {}

DirectionalLight::DirectionalLight() :
	BaseLight(),
	m_direction(vec3(1.0f, 1.0f, 1.0f).normalize()) {}

DirectionalLight::DirectionalLight(const vec3 &color, float intensity, const vec3 &direction) :
	BaseLight(color, intensity),
	m_direction(direction) {}

DirectionalLight::DirectionalLight(const vec3 &direction, const BaseLight &base) :
	BaseLight(base),
	m_direction(direction) {}

PointLight::PointLight() :
	BaseLight(),
	m_atten(0.0f, 0.0f, 1.0f),
	m_pos(0.0f, 0.0f, 0.0f),
	m_range(calcRange(*this)) {}

PointLight::PointLight(const vec3 &color, float intensity, const Attenuation &atten, const vec3 &pos) :
	BaseLight(color, intensity),
	m_atten(atten),
	m_pos(pos),
	m_range(calcRange(*this)) {}

PointLight::PointLight(const Attenuation &atten, const vec3 &pos, const BaseLight &base) :
	BaseLight(base),
	m_atten(atten),
	m_pos(pos),
	m_range(calcRange(*this)) {}

float PointLight::calcRange(const PointLight &pointLight)
{
	float maxColorValue = pointLight.getColor().x > pointLight.getColor().y ? pointLight.getColor().x : pointLight.getColor().y;
	if (pointLight.getColor().z > maxColorValue) maxColorValue = pointLight.getColor().z;
	
	float a = pointLight.getAttenuation().getExponent();
	float b = pointLight.getAttenuation().getLinear();
	float c = pointLight.getAttenuation().getConstant() - COLOR_DEPTH * pointLight.getIntensity() * maxColorValue;
	
	return (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
}

SpotLight::SpotLight() :
	PointLight(),
	m_direction(vec3(1.0f, 1.0f, 1.0f).normalize()),
	m_cutoff(0.7f) {}

SpotLight::SpotLight(const vec3 &color, float intensity, const Attenuation &atten, const vec3 &pos, const vec3 &direction, float cutoff) :
	PointLight(color, intensity, atten, pos),
	m_direction(direction),
	m_cutoff(cutoff) {}

SpotLight::SpotLight(const vec3 &direction, float cutoff, const PointLight &pointLight) :
	PointLight(pointLight),
	m_direction(direction),
	m_cutoff(cutoff) {}