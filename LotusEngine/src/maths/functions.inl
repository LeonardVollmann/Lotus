#include <cmath>

namespace lotus { namespace maths {

	template <>
	inline float sin<float>(float n)
	{
		return std::sinf(n);
	}

	template <>
	inline float cos<float>(float n)
	{
		return std::cosf(n);
	}

	template <>
	inline float tan<float>(float n)
	{
		return std::tanf(n);
	}

	template <>
	inline double sin<double>(double n)
	{
		return std::sin(n);
	}

	template <>
	inline double cos<double>(double n)
	{
		return std::cos(n);
	}

	template <>
	inline double tan<double>(double n)
	{
		return std::tan(n);
	}

	template <>
	inline float asin<float>(float n)
	{
		return std::asinf(n);
	}

	template <>
	inline float acos<float>(float n)
	{
		return std::acosf(n);
	}

	template <>
	inline float atan<float>(float n)
	{
		return std::atanf(n);
	}

	template <>
	inline double asin<double>(double n)
	{
		return std::asin(n);
	}

	template <>
	inline double acos<double>(double n)
	{
		return std::acos(n);
	}

	template <>
	inline double atan<double>(double n)
	{
		return std::atan(n);
	}

	template <>
	inline float sqrt<float>(float n)
	{
		return std::sqrtf(n);
	}

	template <>
	inline double sqrt<double>(double n)
	{
		return std::sqrt(n);
	}

	template <typename T>
	inline T toRadians(T deg)
	{
		return deg / T(180) * M_PI;
	}

	template <typename T>
	inline T toDegrees(T rad)
	{
		return rad / M_PI * T(180);
	}

} }