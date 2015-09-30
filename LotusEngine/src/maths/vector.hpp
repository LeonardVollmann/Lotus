#ifndef LOTUS_VECTOR_HPP_INCLUDED
#define LOTUS_VECTOR_HPP_INCLUDED

#include <cstring>

namespace lotus { namespace maths {
	
	template <typename T>
	struct Quaternion;
	
	template <typename T, unsigned int N>
	struct Vector
	{
		T v[N];
		
		Vector(T t = (T) 0);
		Vector(T t[N]);
	};
	
	template <typename T, unsigned int N>
	bool operator==(const Vector<T, N> &l, const Vector<T, N> &r);
	template <typename T, unsigned int N>
	bool operator!=(const Vector<T, N> &l, const Vector<T, N> &r);
	
	template <typename T, unsigned int N>
	T lengthSquared(const Vector<T, N> &Vector);
	template <typename T, unsigned int N>
	T length(const Vector<T, N> &Vector);
	
	template <typename T, unsigned int N>
	Vector<T, N> normalized(const Vector<T, N> &vec);
	
	template <typename T, unsigned int N>
	Vector<T, N> add(const Vector<T, N> &l, const Vector<T, N> &r);
	template <typename T, unsigned int N>
	Vector<T, N> sub(const Vector<T, N> &l, const Vector<T, N> &r);
	template <typename T, unsigned int N>
	Vector<T, N> mul(const Vector<T, N> &l, const Vector<T, N> &r);
	template <typename T, unsigned int N>
	Vector<T, N> div(const Vector<T, N> &l, const Vector<T, N> &r);
	
	template <typename T, unsigned int N>
	Vector<T, N> add(const Vector<T, N> &l, T r);
	template <typename T, unsigned int N>
	Vector<T, N> sub(const Vector<T, N> &l, T nr);
	template <typename T, unsigned int N>
	Vector<T, N> mul(const Vector<T, N> &l, T r);
	template <typename T, unsigned int N>
	Vector<T, N> div(const Vector<T, N> &l, T r);
	
	template <typename T, unsigned int N>
	inline Vector<T, N> operator+(const Vector<T, N> &l, const Vector<T, N> &r) { return add(l, r); }
	template <typename T, unsigned int N>
	inline Vector<T, N> operator-(const Vector<T, N> &l, const Vector<T, N> &r) { return sub(l, r); }
	template <typename T, unsigned int N>
	inline Vector<T, N> operator*(const Vector<T, N> &l, const Vector<T, N> &r) { return mul(l, r); }
	template <typename T, unsigned int N>
	inline Vector<T, N> operator/(const Vector<T, N> &l, const Vector <T, N> &r) { return div(l, r); }
	
	template <typename T, unsigned int N>
	inline Vector<T, N> operator+(const Vector<T, N> &l, T r) { return add(l, r); }
	template <typename T, unsigned int N>
	inline Vector<T, N> operator-(const Vector<T, N> &l, T r) { return sub(l, r); }
	template <typename T, unsigned int N>
	inline Vector<T, N> operator*(const Vector<T, N> &l, T r) { return mul(l, r); }
	template <typename T, unsigned int N>
	inline Vector<T, N> operator/(const Vector<T, N> &l, T r) { return div(l, r); }
	
	template <typename T, unsigned int N>
	inline void operator+=(Vector<T, N> &l, const Vector<T, N> &r) { l = l + r; }
	template <typename T, unsigned int N>
	inline void operator-=(Vector<T, N> &l, const Vector<T, N> &r) { l = l - r; }
	template <typename T, unsigned int N>
	inline void operator*=(Vector<T, N> &l, const Vector<T, N> &r) { l = l * r; }
	template <typename T, unsigned int N>
	inline void operator/=(Vector<T, N> &l, const Vector<T, N> &r) { l = l / r; }
	
	template <typename T, unsigned int N>
	inline void operator+=(Vector<T, N> &l, T r) { l = l + r; }
	template <typename T, unsigned int N>
	inline void operator-=(Vector<T, N> &l, T r) { l = l - r; }
	template <typename T, unsigned int N>
	inline void operator*=(Vector<T, N> &l, T r) { l = l * r; }
	template <typename T, unsigned int N>
	inline void operator/=(Vector<T, N> &l, T r) { l = l / r; }
	
	template <typename T>
	struct Vector2 : Vector<T, 2>
	{
		T &x;
		T &y;
		
		Vector2(T t = (T) 0) :
			Vector<T, 2>(t),
			x(this->v[0]),
			y(this->v[1]) {}
		
		Vector2(T x, T y) :
			Vector2()
		{
			this->v[0] = x;
			this->v[1] = y;
		}
		
		inline Vector2 &operator=(const Vector2 &other)
		{
			memcpy(this->v, other.v, 2 * sizeof(T));
			return *this;
		}
		
		inline Vector2 &operator=(const Vector<T, 2> &other)
		{
			memcpy(this->v, other.v, 2 * sizeof(T));
			return *this;
		}
		
		Vector2(const Vector2 &other) :
			Vector2()
		{
			operator=(other);
		}
		
		Vector2(const Vector<T, 2> &other) :
			Vector2()
		{
			operator=(other);
		}
	};
	
	template <typename T>
	struct Vector3 : Vector<T, 3>
	{
		T &x;
		T &y;
		T &z;
		
		Vector3(T t = (T) 0) :
			Vector<T, 3>(t),
			x(this->v[0]),
			y(this->v[1]),
			z(this->v[2]) {}
		
		Vector3(T x, T y, T z) :
			Vector3()
		{
			this->v[0] = x;
			this->v[1] = y;
			this->v[2] = z;
		}
		
		inline Vector3 &operator=(const Vector3 &other)
		{
			memcpy(this->v, other.v, 3 * sizeof(T));
			return *this;
		}
		
		inline Vector3 &operator=(const Vector<T, 3> &other)
		{
			memcpy(this->v, other.v, 3 * sizeof(T));
			return *this;
		}
		
		Vector3(const Vector3 &other) :
			Vector3()
		{
			operator=(other);
		}
		
		Vector3(const Vector<T, 3> &other) :
			Vector3()
		{
			operator=(other);
		}
	};
	
	template <typename T>
	Vector3<T> cross(const Vector3<T> &l, const Vector3<T> &r);
	template <typename T>
	Vector3<T> rotate(const Vector3<T> &v, const Quaternion<T> &q);
	
	template <typename T>
	struct Vector4 : Vector<T, 4>
	{
		T &x;
		T &y;
		T &z;
		T &w;
		
		Vector4(T t = (T) 0) :
			Vector<T, 4>(t),
			x(this->v[0]),
			y(this->v[1]),
			z(this->v[2]),
			w(this->v[3]) {}
		
		Vector4(T x, T y, T z, T w) :
			Vector4()
		{
			this->v[0] = x;
			this->v[1] = y;
			this->v[2] = z;
			this->v[3] = w;
		}
		
		inline Vector4 &operator=(const Vector4 &other)
		{
			memcpy(this->v, other.v, 3 * sizeof(T));
			return *this;
		}
		
		inline Vector4 &operator=(const Vector<T, 4> &other)
		{
			memcpy(this->v, other.v, 3 * sizeof(T));
			return *this;
		}
		
		Vector4(const Vector4 &other) :
			Vector4()
		{
			operator=(other);
		}
		
		Vector4(const Vector<T, 4> &other) :
			Vector4()
		{
			operator=(other);
		}
	};
	
	typedef Vector2<float> Vector2f;
	typedef Vector3<float> Vector3f;
	typedef Vector4<float> Vector4f;
	typedef Vector2<double> Vector2d;
	typedef Vector3<double> Vector3d;
	typedef Vector4<double> Vector4d;
	
} }

#include "vector.inl"

#endif