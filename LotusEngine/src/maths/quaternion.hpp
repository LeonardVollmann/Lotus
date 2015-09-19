#ifndef LOTUS_QUATERNION_HPP_INCLUDED
#define LOTUS_QUATERNION_HPP_INCLUDED

#include "vector.hpp"

namespace lotus { namespace math {

	template <typename T>
	struct quat
	{
		T x;
		T y;
		T z;
		T w;
		
		quat(T x = (T) 0, T y = (T) 0, T z = (T) 0, T w = (T) 1);
		quat(const vec3<T> &axis, T angle);
	};
	
	template <typename T>
	bool operator==(const quat<T> &l, const quat<T> &r);
	template <typename T>
	bool operator!=(const quat<T> &l, const quat<T> &r);
	
	template <typename T>
	quat<T> mul(const quat<T> &l, T r);
	template <typename T>
	quat<T> mul(const quat<T> &l, const quat<T> &r);
	template <typename T>
	quat<T> mul(const quat<T> &l, const vec3<T> &r);
	
	template <typename T>
	T lengthSquared(const quat<T> &q);
	template <typename T>
	T length(const quat<T> &q);
	
	template <typename T>
	quat<T> normalized(const quat<T> &q);
	template <typename T>
	quat<T> conjugate(const quat<T> &q);
	
	template <typename T>
	inline quat<T> operator*(const quat<T> &l, T r) { return mul(l, r); }
	template <typename T>
	inline quat<T> operator*(const quat<T> &l, const quat<T> &r) { return mul(l, r); }
	template <typename T>
	inline quat<T> operator*(const quat<T> &l, const vec3<T> &r) { return mul(l, r); }
	
	template <typename T>
	inline void operator*=(quat<T> &l, T r) { l = l * r; }
	template <typename T>
	inline void operator*=(quat<T> &l, const quat<T> &r) { l = l * r; }
	template <typename T>
	inline void operator*=(quat<T> &l, const vec3<T> &r) { l = l * r; }
	
	typedef quat<float> fquat;
	typedef quat<double> dquat;
	
} }

#endif