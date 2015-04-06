#ifndef LOTUS_LIGHTING_HPP_INCLUDED
#define LOTUS_LIGHTING_HPP_INCLUDED

#include "../maths/lotus_vec3.hpp"

namespace lotus { namespace graphics { 

	struct BaseLight
	{
		maths::vec3 color;
		float intensity;

		BaseLight(const maths::vec3 &color, float intensity)
		{
			this->color = color;
			this->intensity = intensity; 
		}
	};

	struct DirectionalLight
	{
		BaseLight base;
		maths::vec3 direction;

		DirectionalLight(const BaseLight &baseLight, const maths::vec3 &direction) :
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
		BaseLight base;
		Attenuation atten;
		maths::vec3 pos;

		PointLight(const BaseLight &baseLight, const Attenuation &attenuation, const maths::vec3 &pos) :
			base(baseLight),
			atten(attenuation)
		{
			this->pos = pos;
		}
	};

} }

#endif