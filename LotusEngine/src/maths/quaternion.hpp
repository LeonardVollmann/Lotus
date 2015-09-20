#ifndef LOTUS_QUATERNION_HPP_INCLUDED
#define LOTUS_QUATERNION_HPP_INCLUDED

#include "vector.hpp"

namespace lotus { namespace math {

	template <typename T>
	struct Quaternion
	{
		T x;
		T y;
		T z;
		T w;
		
		Quaternion(T x = (T) 0, T y = (T) 0, T z = (T) 0, T w = (T) 1);
		Quaternion(const vec3<T> &axis, T angle);
	};
	
	template <typename T>
	bool operator==(const Quaternion<T> &l, const Quaternion<T> &r);
	template <typename T>
	bool operator!=(const Quaternion<T> &l, const Quaternion<T> &r);
	
	template <typename T>
	Quaternion<T> mul(const Quaternion<T> &l, T r);
	template <typename T>
	Quaternion<T> mul(const Quaternion<T> &l, const Quaternion<T> &r);
	template <typename T>
	Quaternion<T> mul(const Quaternion<T> &l, const vec3<T> &r);
	
	template <typename T>
	T lengthSquared(const Quaternion<T> &q);
	template <typename T>
	T length(const Quaternion<T> &q);
	
	template <typename T>
	Quaternion<T> normalized(const Quaternion<T> &q);
	template <typename T>
	Quaternion<T> conjugate(const Quaternion<T> &q);
	
	template <typename T>
	inline Quaternion<T> operator*(const Quaternion<T> &l, T r) { return mul(l, r); }
	template <typename T>
	inline Quaternion<T> operator*(const Quaternion<T> &l, const Quaternion<T> &r) { return mul(l, r); }
	template <typename T>
	inline Quaternion<T> operator*(const Quaternion<T> &l, const vec3<T> &r) { return mul(l, r); }
	
	template <typename T>
	inline void operator*=(Quaternion<T> &l, T r) { l = l * r; }
	template <typename T>
	inline void operator*=(Quaternion<T> &l, const Quaternion<T> &r) { l = l * r; }
	template <typename T>
	inline void operator*=(Quaternion<T> &l, const vec3<T> &r) { l = l * r; }
	
	typedef Quaternion<float> fquat;
	typedef Quaternion<double> dquat;
	
} }

#endif