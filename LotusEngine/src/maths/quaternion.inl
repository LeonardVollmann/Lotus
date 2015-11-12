#include "functions.hpp"

namespace lotus { namespace maths {

	template <typename T>
	bool operator==(const quat<T> &l, const quat<T> &r)
	{
		return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
	}

	template <typename T>
	bool operator!=(const quat<T> &l, const quat<T> &r)
	{
		return !l == r;
	}

	template <typename T>
	T lengthSquared(const quat<T> &q)
	{
		return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	}

	template <typename T>
	T length(const quat<T> &q)
	{
		return sqrt<T>(lengthSquared(q));
	}

	template <typename T>
	quat<T> normalize(const quat<T> &q)
	{
		const T l = length(q);
		return quat<T>(q.x / l, q.y / l, q.z / l, q.w / l);
	}

	template <typename T>
	quat<T> conjugate(const quat<T> &q)
	{
		return quat<T>(-q.x, -q.y, -q.z, q.w);
	}

	template <typename T>
	quat<T> mul(const quat<T> &l, T r)
	{
		quat<T> result;
		result.x = l.x * r;
		result.y = l.y * r;
		result.z = l.z * r;
		result.w = l.w * r;

		return result;
	}

	template <typename T>
	quat<T> mul(const quat<T> &l, const quat<T> &r)
	{
		const T w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;
		const T x = l.x * r.w + l.w * r.x + l.y * r.z - l.z * r.y;
		const T y = l.y * r.w + l.w * r.y + l.z * r.x - l.x * r.z;
		const T z = l.z * r.w + l.w * r.z + l.x * r.y - l.y * r.x;

		return quat<T>(x, y, z, w);
	}

	template <typename T>
	quat<T> mul(const quat<T> &l, const vec<T, 3> &r)
	{
		const float w = -l.x * r.x - l.y * r.y - l.z * r.z;
		const float x =  l.w * r.x + l.y * r.z - l.z * r.y;
		const float y =  l.w * r.y + l.z * r.x - l.x * r.z;
		const float z =  l.w * r.z + l.x * r.y - l.y * r.x;

		return quat<T>(x, y, z, w);
	}

	template <typename T>
	vec<T, 3> getForward(const quat<T> &q)
	{
		return rotate(vec<T, 3>(0, 0, -1), q);
	}

	template <typename T>
	vec<T, 3> getBack(const quat<T> &q)
	{
		return rotate(vec<T, 3>(0, 0, 1), q);
	}

	template <typename T>
	vec<T, 3> getUp(const quat<T> &q)
	{
		return rotate(vec<T, 3>(0, 1, 0), q);
	}

	template <typename T>
	vec<T, 3> getDown(const quat<T> &q)
	{
		return rotate(vec<T, 3>(0, -1, 0), q);
	}

	template <typename T>
	vec<T, 3> getRight(const quat<T> &q)
	{
		return rotate(vec<T, 3>(1, 0, 0), q);
	}

	template <typename T>
	vec<T, 3> getLeft(const quat<T> &q)
	{
		return rotate(vec<T, 3>(-1, 0, 0), q);
	}

	template <typename T>
	quat<T> axisAngle(const vec<T, 3> &axis, T angle)
	{
		quat<T> result;

		const T sinHalfAngle = sin<T>(angle / (T) 2);
		const T cosHalfAngle = cos<T>(angle / (T) 2);

		result.x = axis.x * sinHalfAngle;
		result.y = axis.y * sinHalfAngle;
		result.z = axis.z * sinHalfAngle;
		result.w = cosHalfAngle;

		return result;
	}

	template <typename T>
	vec<T, 3> rotate(const vec<T, 3> &v, const quat<T> &q)
	{
		return (q * v * conjugate(q)).xyz;
	}

} }