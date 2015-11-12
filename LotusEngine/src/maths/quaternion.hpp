#ifndef LOTUS_QUATERNION_HPP_INCLUDED
#define LOTUS_QUATERNION_HPP_INCLUDED

#include "types.hpp"

namespace lotus { namespace maths {

	template <typename T>
	bool operator==(const quat<T> &l, const quat<T> &r);
	template <typename T>
	bool operator!=(const quat<T> &l, const quat<T> &r);

	template <typename T>
	T lengthSquared(const quat<T> &q);
	template <typename T>
	T length(const quat<T> &q);

	template <typename T>
	quat<T> normalize(const quat<T> &q);
	template <typename T>
	quat<T> conjugate(const quat<T> &q);

	template <typename T>
	quat<T> mul(const quat<T> &l, T r);
	template <typename T>
	quat<T> mul(const quat<T> &l, const quat<T> &r);
	template <typename T>
	quat<T> mul(const quat<T> &l, const vec<T, 3> &r);

	template <typename T>
	vec<T, 3> getForward(const quat<T> &q);
	template <typename T>
	vec<T, 3> getBack(const quat<T> &q);
	template <typename T>
	vec<T, 3> getUp(const quat<T> &q);
	template <typename T>
	vec<T, 3> getDown(const quat<T> &q);
	template <typename T>
	vec<T, 3> getRight(const quat<T> &q);
	template <typename T>
	vec<T, 3> getLeft(const quat<T> &q);

	template <typename T>
	quat<T> axisAngle(const vec<T, 3> &axis, T angle);

	template <typename T>
	vec<T, 3> rotate(const vec<T, 3> &v, const quat<T> &q);

	template <typename T>
	inline quat<T> operator*(const quat<T> &l, T r) { return mul(l, r); }
	template <typename T>
	inline quat<T> operator*(const quat<T> &l, const quat<T> &r) { return mul(l, r); }
	template <typename T>
	inline quat<T> operator*(const quat<T> &l, const vec<T, 3> &r) { return mul(l, r); }

	template <typename T>
	inline void operator*=(quat<T> &l, T r) { l = l * r; }
	template <typename T>
	inline void operator*=(quat<T> &l, const quat<T> &r) { l = l * r; }
	template <typename T>
	inline void operator*=(quat<T> &l, const vec<T, 3> &r) { l = l * r; }

} }

#include "quaternion.inl"

#endif