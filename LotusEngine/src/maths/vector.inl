#include "functions.hpp"

namespace lotus { namespace maths {

	template <typename T>
	bool operator==(const vec<T, 2> &l, const vec<T, 2> &r)
	{
		return (l.x == r.x) && (l.y == r.y);
	}

	template <typename T>
	bool operator!=(const vec<T, 2> &l, const vec<T, 2> &r)
	{
		return !(l == r);
	}

	template <typename T>
	T lengthSquared(const vec<T, 2> &vec)
	{
		return vec.x * vec.x + vec.y * vec.y;
	}

	template <typename T>
	T length(const vec<T, 2> &vec)
	{
		return sqrtf(lengthSquared(vec));
	}

	template <typename T>
	vec<T, 2> add(const vec<T, 2> &l, const vec<T, 2> &r)
	{
		vec<T, 2> result;
		result.x = l.x + r.x;
		result.y = l.y + r.y;
		return result;
	}

	template <typename T>
	vec<T, 2> sub(const vec<T, 2> &l, const vec<T, 2> &r)
	{
		vec<T, 2> result;
		result.x = l.x - r.x;
		result.y = l.y - r.y;
		return result;
	}

	template <typename T>
	vec<T, 2> mul(const vec<T, 2> &l, const vec<T, 2> &r)
	{
		vec<T, 2> result;
		result.x = l.x * r.x;
		result.y = l.y * r.y;
		return result;
	}

	template <typename T>
	vec<T, 2> div(const vec<T, 2> &l, const vec<T, 2> &r)
	{
		vec<T, 2> result;
		result.x = l.x / r.x;
		result.y = l.y / r.y;
		return result;
	}

	template <typename T>
	vec<T, 2> mul(const vec<T, 2> &l, T r)
	{
		vec<T, 2> result;
		result.x = l.x * r;
		result.y = l.x * r;
		return result;
	}

	template <typename T>
	vec<T, 2> div(const vec<T, 2> &l, T r)
	{
		vec<T, 2> result;
		result.x = l.x / r;
		result.y = l.x / r;
		return result;
	}

	template <typename T>
	bool operator==(const vec<T, 3> &l, const vec<T, 3> &r)
	{
		return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
	}

	template <typename T>
	bool operator!=(const vec<T, 3> &l, const vec<T, 3> &r)
	{
		return !(l == r);
	}

	template <typename T>
	T lengthSquared(const vec<T, 3> &vec)
	{
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	}

	template <typename T>
	T length(const vec<T, 3> &vec)
	{
		return sqrtf(lengthSquared(vec));
	}

	template <typename T>
	vec<T, 3> add(const vec<T, 3> &l, const vec<T, 3> &r)
	{
		vec<T, 3> result;
		result.x = l.x + r.x;
		result.y = l.y + r.y;
		result.z = l.z + r.z;
		return result;
	}

	template <typename T>
	vec<T, 3> sub(const vec<T, 3> &l, const vec<T, 3> &r)
	{
		vec<T, 3> result;
		result.x = l.x - r.x;
		result.y = l.y - r.y;
		result.z = l.z - r.z;
		return result;
	}

	template <typename T>
	vec<T, 3> mul(const vec<T, 3> &l, const vec<T, 3> &r)
	{
		vec<T, 3> result;
		result.x = l.x * r.x;
		result.y = l.y * r.y;
		result.z = l.z * r.z;
		return result;
	}

	template <typename T>
	vec<T, 3> div(const vec<T, 3> &l, const vec<T, 3> &r)
	{
		vec<T, 3> result;
		result.x = l.x / r.x;
		result.y = l.y / r.y;
		result.z = l.z / r.z;
		return result;
	}

	template <typename T>
	vec<T, 3> mul(const vec<T, 3> &l, T r)
	{
		vec<T, 3> result;
		result.x = l.x * r;
		result.y = l.y * r;
		result.z = l.z * r;
		return result;
	}

	template <typename T>
	vec<T, 3> div(const vec<T, 3> &l, T r)
	{
		vec<T, 3> result(l);
		result.x = l.x / r;
		result.y = l.y / r;
		result.z = l.z / r;
		return result;
	}

	template <typename T>
	bool operator==(const vec<T, 4> &l, const vec<T, 4> &r)
	{
		return (l.x == r.x) && (l.y == r.y) && (l.z == r.z) && (l.w == r.w);
	}

	template <typename T>
	bool operator!=(const vec<T, 4> &l, const vec<T, 4> &r)
	{
		return !(l == r);
	}

	template <typename T>
	T lengthSquared(const vec<T, 4> &vec)
	{
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
	}

	template <typename T>
	T length(const vec<T, 4> &vec)
	{
		return sqrt<T>(lengthSquared(vec));
	}

	template <typename T>
	vec<T, 4> add(const vec<T, 4> &l, const vec<T, 4> &r)
	{
		vec<T, 4> result;
		result.x = l.x + r.x;
		result.y = l.y + r.y;
		result.z = l.z + r.z;
		result.w = l.w + r.w;
		return result;
	}

	template <typename T>
	vec<T, 4> sub(const vec<T, 4> &l, const vec<T, 4> &r)
	{
		vec<T, 4> result;
		result.x = l.x - r.x;
		result.y = l.y - r.y;
		result.z = l.z - r.z;
		result.w = l.w - r.w;
		return result;
	}

	template <typename T>
	vec<T, 4> mul(const vec<T, 4> &l, const vec<T, 4> &r)
	{
		vec<T, 4> result;
		result.x = l.x * r.x;
		result.y = l.y * r.y;
		result.z = l.z * r.z;
		result.w = l.w * r.w;
		return result;
	}

	template <typename T>
	vec<T, 4> div(const vec<T, 4> &l, const vec<T, 4> &r)
	{
		vec<T, 4> result;
		result.x = l.x / r.x;
		result.y = l.y / r.y;
		result.z = l.z / r.z;
		result.w = l.w / r.w;
		return result;
	}

	template <typename T>
	vec<T, 4> mul(const vec<T, 4> &l, T r)
	{
		vec<T, 4> result;
		result.x = l.x * r;
		result.y = l.y * r;
		result.z = l.z * r;
		result.w = l.w * r;
		return result;
	}

	template <typename T>
	vec<T, 4> div(const vec<T, 4> &l, T r)
	{
		vec<T, 4> result;
		result.x = l.x / r;
		result.y = l.y / r;
		result.z = l.z / r;
		result.w = l.w / r;
		return result;
	}

	template <typename T, unsigned int N>
	vec<T, N> normalize(const vec<T, N> &vec)
	{
		return vec / length(vec);
	}

	template <typename T>
	vec<T, 3> cross(const vec<T, 3> &l, const vec<T, 3> &r)
	{
		vec<T, 3> result;
		result.x = l.y * r.z - l.z * r.y;
		result.y = l.z * r.x - l.x * r.z;
		result.z = l.x * r.y - l.y * r.x;
		return result;
	}

} }