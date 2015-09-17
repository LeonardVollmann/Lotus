#include "vector.hpp"

#include <cmath>

namespace lotus { namespace math {
	
	template <typename T, unsigned int N>
	vec<T, N>::vec(T t)
	{
		for (unsigned int i = 0; i < N; i++)
		{
			v[i] = t;
		}
	}
	
	template <typename T, unsigned int N>
	T lengthSquared(const vec<T, N> &vec)
	{
		T result;
		for (unsigned int i = 0; i < N; i++)
		{
			result += vec.v[i] * vec.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	T length(const vec<T, N> &vec)
	{
		return (T) sqrt(lengthSquared(vec));
	}
	
	template <typename T, unsigned int N>
	vec<T, N> normalized(const vec<T, N> &vec)
	{
		return vec(vec / length(vec));
	}
	
	template <typename T, unsigned int N>
	T dot(const vec<T, N> &l, const vec<T, N> &r)
	{
		T result;
		for (unsigned int i = 0; i < N; i++)
		{
			result += l.v[i] * r.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	vec<T, N> add(const vec<T, N> &l, const vec<T, N> &r)
	{
		vec<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] + r.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	vec<T, N> sub(const vec<T, N> &l, const vec<T, N> &r)
	{
		vec<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] - r.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	vec<T, N> mul(const vec<T, N> &l, const vec<T, N> &r)
	{
		vec<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] * r.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	vec<T, N> div(const vec<T, N> &l, const vec<T, N> &r)
	{
		vec<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] / r.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	vec<T, N> add(const vec<T, N> &l, T r)
	{
		vec<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] + r;
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	vec<T, N> sub(const vec<T, N> &l, T r)
	{
		vec<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] - r;
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	vec<T, N> mul(const vec<T, N> &l, T r)
	{
		vec<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] * r;
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	vec<T, N> div(const vec<T, N> &l, T r)
	{
		vec<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] / r;
		}
		return result;
	}
	
	template <typename T>
	vec3<T> cross(const vec3<T> &l, const vec3<T> &r)
	{
		vec3<T> result;
		result.x = l.y * r.z - l.z * r.y;
		result.y = l.z * r.x - l.x * r.z;
		result.z = l.x * r.y - l.y * r.x;
		return result;
	}
	
	template class vec2<float>;
	template class vec3<float>;
	template class vec4<float>;
	template class vec2<double>;
	template class vec3<double>;
	template class vec4<double>;
	
} }