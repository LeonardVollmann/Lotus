#ifndef LOTUS_VECTOR_HPP_INCLUDED
#define LOTUS_VECTOR_HPP_INCLUDED

namespace lotus { namespace math {
	
	template <typename T>
	struct Quaternion;
	
	template <typename T, unsigned int N>
	struct Vector
	{
		T v[N];
		
		Vector(T t = (T) 0);
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
	struct vec2 : Vector<T, 2>
	{
		T &x = this->v[0];
		T &y = this->v[1];
	};
	
	template <typename T>
	struct vec3 : Vector<T, 3>
	{
		T &x = this->v[0];
		T &y = this->v[1];
		T &z = this->v[3];
	};
	
	template <typename T>
	vec3<T> cross(const vec3<T> &l, const vec3<T> &r);
	template <typename T>
	vec3<T> rotate(const vec3<T> &v, const Quaternion<T> &q);
	
	template <typename T>
	struct vec4 : Vector<T, 4>
	{
		T &x = this->v[0];
		T &y = this->v[1];
		T &z = this->v[2];
		T &w = this->v[3];
	};
	
	typedef vec2<float> fvec2;
	typedef vec3<float> fvec3;
	typedef vec4<float> fvec4;
	typedef vec2<double> dvec2;
	typedef vec3<double> dvec3;
	typedef vec4<double> dvec4;
	
} }

#endif