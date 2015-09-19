#include "quaternion.hpp"

#include <cmath>

namespace lotus { namespace math {

	template <typename T>
	quat<T>::quat(T x, T y, T z, T w) :
		x(x),
		y(y),
		z(z),
		w(w) {}
	
	template <typename T>
	quat<T>::quat(const vec3<T> &axis, T angle)
	{
		const T sinHalfAngle = (T) sinf(angle / (T) 2);
		const T cosHalfAngle = (T) cosf(angle / (T) 2);
		
		x = axis.x * sinHalfAngle;
		y = axis.y * sinHalfAngle;
		z = axis.z * sinHalfAngle;
		w = cosHalfAngle;
	}
	
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
	quat<T> mul(const quat<T> &l, const vec3<T> &r)
	{
		const float w = -l.x * r.x - l.y * r.y - l.z * r.z;
		const float x =  l.w * r.x + l.y * r.z - l.z * r.y;
		const float y =  l.w * r.y + l.z * r.x - l.x * r.z;
		const float z =  l.w * r.z + l.x * r.y - l.y * r.x;
		
		return quat<T>(x, y, z, w);
	}
	
	template <typename T>
	T lengthSquared(const quat<T> &q)
	{
		return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	}
	
	template <typename T>
	T length(const quat<T> &q)
	{
		return (T) sqrtf((float) lengthSquared(q));
	}
	
	template <typename T>
	quat<T> normalized(const quat<T> &q)
	{
		return quat<T>(q) * ((T) 1 / length(q));
	}
	
	template <typename T>
	quat<T> conjugate(const quat<T> &q)
	{
		return quat<T>(-q.x, -q.y, -q.z, q.w);
	}
	
	template class quat<float>;
	template class quat<double>;
	
} }