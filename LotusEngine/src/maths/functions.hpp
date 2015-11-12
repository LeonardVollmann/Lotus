#ifndef LOTUS_MATHS_FUNCTIONS_HPP_INCLUDED
#define LOTUS_MATHS_FUNCTIONS_HPP_INCLUDED

namespace lotus { namespace maths {

	template <typename T>
	inline T sin(T n);
	template <typename T>
	inline T cos(T n);
	template <typename T>
	inline T tan(T n);

	template <typename T>
	inline T asin(T n);
	template <typename T>
	inline T acos(T n);
	template <typename T>
	inline T atan(T n);

	template <typename T>
	inline T sqrt(T n);

	template <typename T>
	inline T toRadians(T deg);
	template <typename T>
	inline T toDegrees(T rad);

} }

#include "functions.inl"

#endif