#ifndef LOTUS_LIGHTING_HPP_INCLUDED
#define LOTUS_LIGHTING_HPP_INCLUDED

#include "../maths/lotus_vec3.hpp"

struct BaseLight
{
	vec3 	color;
	float 	intensity;

	BaseLight(const vec3 &color, float intensity)
	{
		this->color = color;
		this->intensity = intensity; 
	}
};

struct DirectionalLight
{
	BaseLight 	base;
	vec3 		direction;

	DirectionalLight(const BaseLight &baseLight, const vec3 &direction) :
		base(baseLight)
	{
		this->direction = direction;
	}
};

struct Attenuation
{
	float constant, linear, exponent;

	Attenuation(float constant, float linear, float exponent)
	{
		this->constant = constant;
		this->linear = linear;
		this->exponent = exponent;
	}
};

struct PointLight
{
	BaseLight 	base;
	Attenuation atten;
	vec3 		pos;
	float 		range;

	PointLight(const BaseLight &baseLight, const Attenuation &attenuation, const vec3 &pos, float range) :
		base(baseLight),
		atten(attenuation)
	{
		this->pos = pos;
		this->range = range;
	}
};

struct SpotLight
{
	PointLight 	pointLight;
	vec3 		direction;
	float 		cutoff;

	SpotLight(const PointLight &point, const vec3 &direction, float cutoff) :
		pointLight(point)
	{
		this->direction = direction;
		this->cutoff = cutoff;
	}
};

#endif