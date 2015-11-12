#ifndef LOTUS_MATRIX_HPP_INCLUDED
#define LOTUS_MATRIX_HPP_INCLUDED

#include "types.hpp"

namespace lotus { namespace maths {

	template <typename T, unsigned int N>
	bool operator==(const mat<T, N> &l, const mat<T, N> &r);
	template <typename T, unsigned int N>
	bool operator!=(const mat<T, N> &l, const mat<T, N> &r);

	template <typename T, unsigned int N>
	mat<T, N> mul(const mat<T, N> &l, const mat<T, N> &r);
	template <typename T, unsigned int M_N, unsigned int V_N>
	vec<T, V_N> mul(const mat<T, M_N> &l, const vec<T, V_N> &r);
	template <typename T, unsigned int N>
	mat<T, N> mul(const mat<T, N> &l, T r);

	template <typename T, unsigned int N>
	mat<T, N> diagonal(T n);
	template <typename T, unsigned int N>
	mat<T, N> identity();

	template <typename T, unsigned int N>
	mat<T, N> transpose(const mat<T, N> &m);

	template <typename T, unsigned int N>
	mat<T, N> translation(const vec<T, N - 1> &translation);

	template <typename T, unsigned int N>
	mat<T, N> scale(const vec<T, N - 1> &scale);

	template <typename T, unsigned int N>
	mat<T, N> rotation(T angle);
	template <typename T, unsigned int N>
	mat<T, N> rotation(T x, T y, T z);
	template <typename T, unsigned int N>
	mat<T, N> rotation(const vec<T, 3> &f, const vec<T, 3> &u, const vec<T, 3> &r);
	template <typename T, unsigned int N>
	mat<T, N> rotation(const quat<T> &rot);
	template <typename T, unsigned int N>
	mat<T, N> rotation(const vec<T, N> &axis, T angle);

	template <typename T>
	mat<T, 4> orthographic(T left, T right, T bottom, T top, T near, T far);
	template <typename T>
	mat<T, 4> perspective(T fov, T aspectRatio, T near, T far);

	template <typename T, unsigned int N>
	inline mat<T, N> operator*(const mat<T, N> &l, const mat<T, N> &r) { return mul(l, r); }
	template <typename T, unsigned int M_N, unsigned int V_N>
	inline vec<T, V_N> operator*(const mat<T, M_N> &l, const vec<T, V_N> &r) { return mul(l, r); }
	template <typename T, unsigned int N>
	inline mat<T, N> operator*(const mat<T, N> &l, T r) { return mul(l, r); }

} }

#include "matrix.inl"

#endif