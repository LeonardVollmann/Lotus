#ifndef MATHS_FUNC_HPP
#define MATHS_FUNC_HPP

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