#ifndef LOTUS_MATRIX_HPP_INCLUDED
#define LOTUS_MATRIX_HPP_INCLUDED

namespace lotus { namespace maths {
	
	template <typename T, unsigned int N>
	struct Vector;
	
	template <typename T>
	struct Quaternion;
	
	template <typename T, unsigned int N>
	struct Matrix
	{
		union
		{
			T elements[N * N];
			Vector<T, N> columns[N];
		};
		
		Matrix(T diagonal = (T) 0);
	};
	
	template <typename T, unsigned int N>
	bool operator==(const Matrix<T, N> &l, const Matrix<T, N> &r);
	template <typename T, unsigned int N>
	bool operator!=(const Matrix<T, N> &l, const Matrix<T, N> &r);
	
	template <typename T, unsigned int N>
	Matrix<T, N> mul(const Matrix<T, N> &l, const Matrix<T, N> &r);
	template <typename T, unsigned int N>
	Matrix<T, N> mul(const Matrix<T, N> &l, T r);
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> operator*(const Matrix<T, N> &l, const Matrix<T, N> &r) { return mul(l, r); }
	template <typename T, unsigned int N>
	inline Matrix<T, N> operator*(const Matrix<T, N> &l, T r) { return mul(l, r); }
	
	template <typename T, unsigned int N>
	inline void operator*=(const Matrix<T, N> &l, const Matrix<T, N> &r) { l = l * r; }
	template <typename T, unsigned int N>
	inline void operator*=(const Matrix<T, N> &l, T r) { l = l * r; }
	
	template <typename T, unsigned int N>
	Matrix<T, N> identity();
	
	template <typename T, unsigned int N>
	Matrix<T, N> transposed(const Matrix<T, N> &m);
	
	template <typename T, unsigned int N>
	Matrix<T, N> translation(const Vector<T, N - 1> &translation);
	template <typename T, unsigned int N>
	Matrix<T, N> scale(const Vector<T, N - 1> &scale);
	
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(T angle);
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(T x, T y, T z);
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(const Vector<T, 3> &f, const Vector<T, 3> &u, const Vector<T, 3> &r);
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(const Quaternion<T> &rot);
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(const Vector<T, N> &axis, T angle);
	
	template <typename T>
	Matrix<T, 4> orthographic(T left, T right, T bottom, T top, T near, T far);
	template <typename T>
	Matrix<T, 4> perspective(T fov, T aspectRatio, T near, T far);
	
	typedef Matrix<float, 2> Matrix2f;
	typedef Matrix<float, 3> Matrix3f;
	typedef Matrix<float, 4> Matrix4f;
	typedef Matrix<double, 2> Matrix2d;
	typedef Matrix<double, 3> Matrix3d;
	typedef Matrix<double, 4> Matrix4d;
	
} }

#include "matrix.inl"

#endif