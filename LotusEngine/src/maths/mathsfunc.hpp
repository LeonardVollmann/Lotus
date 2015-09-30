#ifndef LOTUS_MATH_FUNC_HPP_INCLUDED
#define LOTUS_MATH_FUNC_HPP_INCLUDED

#include <cmath>

namespace lotus { namespace maths {
	
	template <typename T>
	inline T sin(T n)
	{
//		#if T == double
//			return sin(n);
//		#else
//			return sinf(n);
//		#endif
		return T(sinf(n));
	}
	
	template <typename T>
	inline T cos(T n)
	{
//		#if T == double
//			return cos(n);
//		#else
//			return cosf(n);
//		#endif
		return T(cosf(n));
	}
	
	template <typename T>
	inline T sqrt(T n)
	{
//		#if T == double
//			return sqrt(n);
//		#else
//			return sqrtf(n);
//		#endif
		return T(sqrtf(n));
	}
	
	template <typename T>
	inline T toRadians(T deg)
	{
		return deg / 180 * M_PI;
	}
	
	template <typename T>
	inline T toDegrees(T rad)
	{
		return rad / M_PI * 180;
	}
	
} }

#endif