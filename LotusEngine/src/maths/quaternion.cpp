#include "quaternion.hpp"

#include <cmath>

namespace lotus { namespace math {

	template <typename T>
	Quaternion<T>::Quaternion(T x, T y, T z, T w) :
		x(x),
		y(y),
		z(z),
		w(w) {}
	
	template <typename T>
	Quaternion<T>::Quaternion(const Vector3<T> &axis, T angle)
	{
		const T sinHalfAngle = (T) sinf(angle / (T) 2);
		const T cosHalfAngle = (T) cosf(angle / (T) 2);
		
		x = axis.x * sinHalfAngle;
		y = axis.y * sinHalfAngle;
		z = axis.z * sinHalfAngle;
		w = cosHalfAngle;
	}
	
	template <typename T>
	bool operator==(const Quaternion<T> &l, const Quaternion<T> &r)
	{
		return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
	}
	
	template <typename T>
	bool operator!=(const Quaternion<T> &l, const Quaternion<T> &r)
	{
		return !l == r;
	}
	
	template <typename T>
	Quaternion<T> mul(const Quaternion<T> &l, T r)
	{
		Quaternion<T> result;
		result.x = l.x * r;
		result.y = l.y * r;
		result.z = l.z * r;
		result.w = l.w * r;
		
		return result;
	}
	
	template <typename T>
	Quaternion<T> mul(const Quaternion<T> &l, const Quaternion<T> &r)
	{
		const T x = l.x * r.w + l.w * r.x + l.y * r.z - l.z * r.y;
		const T y = l.y * r.w + l.w * r.y + l.z * r.x - l.x * r.z;
		const T z = l.z * r.w + l.w * r.z + l.x * r.y - l.y * r.x;
		const T w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;	

		return Quaternion<T>(x, y, z, w);
	}
	
	template <typename T>
	Quaternion<T> mul(const Quaternion<T> &l, const Vector3<T> &r)
	{
		const float w = -l.x * r.x - l.y * r.y - l.z * r.z;
		const float x =  l.w * r.x + l.y * r.z - l.z * r.y;
		const float y =  l.w * r.y + l.z * r.x - l.x * r.z;
		const float z =  l.w * r.z + l.x * r.y - l.y * r.x;
		
		return Quaternion<T>(x, y, z, w);
	}
	
	template <typename T>
	T lengthSquared(const Quaternion<T> &q)
	{
		return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	}
	
	template <typename T>
	T length(const Quaternion<T> &q)
	{
		return (T) sqrtf((float) lengthSquared(q));
	}
	
	template <typename T>
	Quaternion<T> normalized(const Quaternion<T> &q)
	{
		return Quaternion<T>(q) * ((T) 1 / length(q));
	}
	
	template <typename T>
	Quaternion<T> conjugate(const Quaternion<T> &q)
	{
		return Quaternion<T>(-q.x, -q.y, -q.z, q.w);
	}
	
	template class Quaternion<float>;
	template class Quaternion<double>;
	
} }