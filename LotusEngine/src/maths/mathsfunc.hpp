#ifndef LOTUS_MATH_FUNC_HPP_INCLUDED
#define LOTUS_MATH_FUNC_HPP_INCLUDED

#include <cmath>

namespace lotus { namespace math {
	
	template <typename T>
	inline T sin(T n)
	{
		#if T == double
			return sin(n);
		#else
			return sinf(n);
		#endif
	}
	
	template <typename T>
	inline T cos(T n)
	{
		#if T == double
			return cos(n);
		#else
			return cosf(n);
		#endif
	}
	
	template <typename T>
	inline T sqrt(T n)
	{
		#if T == double
			return sqrt(n);
		#else
			return sqrtf(n);
		#endif
	}
	
} }

#endif