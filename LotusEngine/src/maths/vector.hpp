#pragma once

#include "types.hpp"

namespace lotus
{
namespace maths
{

template <typename T, unsigned int N>
bool operator==(const vec<T, N> &l, const vec<T, N> &r);
template <typename T, unsigned int N>
bool operator!=(const vec<T, N> &l, const vec<T, N> &r);

template <typename T, unsigned int N>
T lengthSquared(const vec<T, N> &vec);
template <typename T, unsigned int N>
T length(const vec<T, N> &vec);

template <typename T, unsigned int N>
vec<T, N> add(const vec<T, N> &l, const vec<T, N> &r);
template <typename T, unsigned int N>
vec<T, N> sub(const vec<T, N> &l, const vec<T, N> &r);
template <typename T, unsigned int N>
vec<T, N> mul(const vec<T, N> &l, const vec<T, N> &r);
template <typename T, unsigned int N>
vec<T, N> div(const vec<T, N> &l, const vec<T, N> &r);
template <typename T, unsigned int N>
vec<T, N> mul(const vec<T, N> &l, T r);
template <typename T, unsigned int N>
vec<T, N> div(const vec<T, N> &l, T r);

template <typename T, unsigned int N>
vec<T, N> normalize(const vec<T, N> &vec);

template <typename T, unsigned int N>
inline vec<T, N> operator+(const vec<T, N> &l, const vec<T, N> &r)
{
	return add(l, r);
}

template <typename T, unsigned int N>
inline vec<T, N> operator-(const vec<T, N> &l, const vec<T, N> &r)
{
	return sub(l, r);
}

template <typename T, unsigned int N>
inline vec<T, N> operator*(const vec<T, N> &l, const vec<T, N> &r)
{
	return mul(l, r);
}

template <typename T, unsigned int N>
inline vec<T, N> operator/(const vec<T, N> &l, const vec<T, N> &r)
{
	return div(l, r);
}

template <typename T, unsigned int N>
inline vec<T, N> operator*(const vec<T, N> &l, T r)
{
	return mul(l, r);
}

template <typename T, unsigned int N>
inline vec<T, N> operator/(const vec<T, N> &l, T r)
{
	return div(l, r);
}

template <typename T, unsigned int N>
inline void operator+=(vec<T, N> &l, const vec<T, N> &r)
{
	l = l + r;
}

template <typename T, unsigned int N>
inline void operator-=(vec<T, N> &l, const vec<T, N> &r)
{
	l = l - r;
}

template <typename T, unsigned int N>
inline void operator*=(vec<T, N> &l, const vec<T, N> &r)
{
	l = l * r;
}

template <typename T, unsigned int N>
inline void operator/=(vec<T, N> &l, const vec<T, N> &r)
{
	l = l / r;
}

template <typename T>
vec<T, 3> cross(const vec<T, 3> &l, const vec<T, 3> &r);

} // namespace maths
} // namespace lotus

#include "vector.inl"