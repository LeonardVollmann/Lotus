#ifndef LOTUS_VECTOR_HPP_INCLUDED
#define LOTUS_VECTOR_HPP_INCLUDED

namespace lotus { namespace math {
	
	template <typename T, unsigned int N>
	struct vec
	{
		T v[N];
		
		vec(T t = (T) 0);
	};
	
	template <typename T, unsigned int N>
	bool operator==(const vec<T, N> &l, const vec<T, N> &r);
	template <typename T, unsigned int N>
	bool operator!=(const vec<T, N> &l, const vec<T, N> &r);
	
	template <typename T, unsigned int N>
	T lengthSquared(const vec<T, N> &vec);
	template <typename T, unsigned int N>
	T length(const vec<T, N> &vec);
	
	template <typename T, unsigned int N>
	vec<T, N> normalized(const vec<T, N> &vec);
	
	template <typename T, unsigned int N>
	vec<T, N> add(const vec<T, N> &l, const vec<T, N> &r);
	template <typename T, unsigned int N>
	vec<T, N> sub(const vec<T, N> &l, const vec<T, N> &r);
	template <typename T, unsigned int N>
	vec<T, N> mul(const vec<T, N> &l, const vec<T, N> &r);
	template <typename T, unsigned int N>
	vec<T, N> div(const vec<T, N> &l, const vec<T, N> &r);
	
	template <typename T, unsigned int N>
	vec<T, N> add(const vec<T, N> &l, T r);
	template <typename T, unsigned int N>
	vec<T, N> sub(const vec<T, N> &l, T nr);
	template <typename T, unsigned int N>
	vec<T, N> mul(const vec<T, N> &l, T r);
	template <typename T, unsigned int N>
	vec<T, N> div(const vec<T, N> &l, T r);
	
	template <typename T, unsigned int N>
	inline vec<T, N> operator+(const vec<T, N> &l, const vec<T, N> &r) { return add(l, r); }
	template <typename T, unsigned int N>
	inline vec<T, N> operator-(const vec<T, N> &l, const vec<T, N> &r) { return sub(l, r); }
	template <typename T, unsigned int N>
	inline vec<T, N> operator*(const vec<T, N> &l, const vec<T, N> &r) { return mul(l, r); }
	template <typename T, unsigned int N>
	inline vec<T, N> operator/(const vec<T, N> &l, const vec<T, N> &r) { return div(l, r); }
	
	template <typename T, unsigned int N>
	inline vec<T, N> operator+(const vec<T, N> &l, T r) { return add(l, r); }
	template <typename T, unsigned int N>
	inline vec<T, N> operator-(const vec<T, N> &l, T r) { return sub(l, r); }
	template <typename T, unsigned int N>
	inline vec<T, N> operator*(const vec<T, N> &l, T r) { return mul(l, r); }
	template <typename T, unsigned int N>
	inline vec<T, N> operator/(const vec<T, N> &l, T r) { return div(l, r); }
	
	template <typename T, unsigned int N>
	inline void operator+=(vec<T, N> &l, const vec<T, N> &r) { l = l + r; }
	template <typename T, unsigned int N>
	inline void operator-=(vec<T, N> &l, const vec<T, N> &r) { l = l - r; }
	template <typename T, unsigned int N>
	inline void operator*=(vec<T, N> &l, const vec<T, N> &r) { l = l * r; }
	template <typename T, unsigned int N>
	inline void operator/=(vec<T, N> &l, const vec<T, N> &r) { l = l / r; }
	
	template <typename T, unsigned int N>
	inline void operator+=(vec<T, N> &l, T r) { l = l + r; }
	template <typename T, unsigned int N>
	inline void operator-=(vec<T, N> &l, T r) { l = l - r; }
	template <typename T, unsigned int N>
	inline void operator*=(vec<T, N> &l, T r) { l = l * r; }
	template <typename T, unsigned int N>
	inline void operator/=(vec<T, N> &l, T r) { l = l / r; }
	
	template <typename T>
	struct vec2 : vec<T, 2>
	{
		T &x = this->v[0];
		T &y = this->v[1];
	};
	
	template <typename T>
	struct vec3 : vec<T, 3>
	{
		T &x = this->v[0];
		T &y = this->v[1];
		T &z = this->v[3];
	};
	
	template <typename T>
	vec3<T> cross(const vec3<T> &l, const vec3<T> &r);
	
	template <typename T>
	struct vec4 : vec<T, 4>
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