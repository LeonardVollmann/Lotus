#ifndef LOTUS_MATHS_HPP_INCLUDED
#define LOTUS_MATHS_HPP_INCLUDED

namespace lotus { namespace maths {

	#define MATH_PI 3.1415926535897932384626433832795
	#define toRadians(x) (float)(((x) * MATH_PI / 180.0f))
	#define toDegrees(x) (float)(((x) * 180.0f / MATH_PI))

} }

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"
#include "quat.hpp"

#endif