#ifndef LOTUS_MATHS_FUNC_HPP_INCLUDED
#define LOTUS_MATHS_FUNC_HPP_INCLUDED

#include <cmath>

namespace lotus { namespace maths { 

	float toRadians(float degrees)
	{
		return degrees * (M_PI / 180);
	}

	float toDegrees(float radians)
	{
		return radians * (180 / M_PI);
	}

} }

#endif