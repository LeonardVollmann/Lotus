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

} }

#endif