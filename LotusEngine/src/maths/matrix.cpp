#include "matrix.hpp"
#include "vector.hpp"
#include "quaternion.hpp"
#include "mathsfunc.hpp"

#include <cassert>

namespace lotus { namespace math {
	
	template <typename T, unsigned int N>
	Matrix<T, N>::Matrix(T diagonal)
	{
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int j = 0; j < N; j++)
			{
				if (i == j) elements[j + i * N] = diagonal;
				else elements[j + i * N] = (T) 0;
			}
		}
	}
	
	template <typename T, unsigned int N>
	bool operator==(const Matrix<T, N> &l, const Matrix<T, N> &r)
	{
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int j = 0; j < N; j++)
			{
				if (l[j + i * N] != r[j + i * N]) return false;
			}
		}
		return true;
	}
	
	template <typename T, unsigned int N>
	bool operator!=(const Matrix<T, N> &l, const Matrix<T, N> &r)
	{
		return !l == r;
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> mul(const Matrix<T, N> &l, const Matrix<T, N> &r)
	{
		Matrix<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int j = 0; j < N; j++)
			{
				T n;
				for (unsigned int k = 0; k < N; k++)
				{
					n += l[k + i * N] * r[j + k * N];
				}
				result[j + i * N] = n;
			}
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> mul(const Matrix<T, N> &l, T r)
	{
		Matrix<T, N> result;
		for (unsigned int i = 0; i < N * N; i++)
		{
			result[i] = l[i] * r;
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> identity()
	{
		return Matrix<T, N>((T) 1);
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> transposed(const Matrix<T, N> &m)
	{
		Matrix<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int j = 0; j < N; j++)
			{
				result[j + i * N] = m[i + j * N];
			}
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> translation(const Vector<T, N - 1> &translation)
	{
		Matrix<T, N> result;
		for (unsigned int i = 0; i < N - 1; i++)
		{
			result[N - 1 + i * N] = translation.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> scale(const Vector<T, N - 1> &scale)
	{
		Matrix<T, N> result;
		for (unsigned int i = 0; i < N - 1; i++)
		{
			result[i * (N + 1)] = scale.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(T angle)
	{
		Matrix<T, N> result(1);
		
		T sin = sin(angle);
		T cos = cos(angle);
		
		result[0 + 0 * N] = cos;
		result[1 + 0 * N] = -sin;
		result[0 + 1 * N] = sin;
		result[1 + 1 * N] = cos;
		
		return result;
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(T x, T y, T z)
	{
		Matrix<T, N> rx(1);
		Matrix<T, N> ry(1);
		Matrix<T, N> rz(1);
		
		const T sinx = sin(x);
		const T cosx = cos(x);
		const T siny = sin(y);
		const T cosy = cos(y);
		const T sinz = sin(z);
		const T cosz = cos(z);
		
		rx[1 + 1 * N] = cosx;
		rx[2 + 1 * N] = -sinx;
		rx[1 + 2 * N] = sinx;
		rx[2 + 2 * N] = cosx;
		
		ry[0 + 0 * N] = cosx;
		ry[2 + 0 * N] = -sinx;
		ry[0 + 2 * N] = sinx;
		ry[2 + 2 * N] = cosx;
		
		rz[0 + 0 * N] = cosx;
		rz[1 + 0 * N] = -sinx;
		rz[0 + 1 * N] = sinx;
		rz[1 + 1 * N] = cosx;
		
		return rz * ry * rx;
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(const Vector<T, 3> &f, const Vector<T, 3> &u, const Vector<T, 3> &r)
	{
		Matrix<T, N> result(1);
		
		result[0 + 0 * N] = r.x;
		result[1 + 0 * N] = r.y;
		result[1 + 0 * N] = r.z;
		result[0 + 1 * N] = u.x;
		result[1 + 1 * N] = u.y;
		result[1 + 1 * N] = u.z;
		result[0 + 2 * N] = f.x;
		result[1 + 3 * N] = f.y;
		result[1 + 3 * N] = f.z;
		
		return result;
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(const Quaternion<T> &rot)
	{
		Vector<T, 3> f = Vector<T, 3>(2 * (rot.x * rot.z - rot.w * rot.y), 2.0f * (rot.y * rot.z + rot.w * rot.x), 1.0f - 2.0f * (rot.x * rot.x + rot.y * rot.y));
		Vector<T, 3> u = Vector<T, 3>(2 * (rot.x * rot.y + rot.w * rot.z), 1.0f - 2.0f * (rot.x * rot.x + rot.z * rot.z), 2.0f * (rot.y * rot.z - rot.w * rot.x));
		Vector<T, 3> r = Vector<T, 3>(1 - 2.0f * (rot.y * rot.y + rot.z * rot.z), 2.0f * (rot.x * rot.y - rot.w * rot.z), 2.0f * (rot.x * rot.z + rot.w * rot.y));
		
		return rotation(f, u, r);
	}
	
	template <typename T, unsigned int N>
	Matrix<T, N> rotation(const Vector<T, N> &axis, T angle)
	{
		return rotation(Quaternion<T>(axis, angle));
	}
	
	template <typename T>
	Matrix<T, 4> orthographic(T left, T right, T bottom, T top, T near, T far)
	{
		Matrix<T, 4> result;
		
		result[0 + 0 * 4] = 2.0f / (right - left);
		
		result[1 + 1 * 4] = 2.0f / (top - bottom);
		
		result[2 + 2 * 4] = 2.0f / (near - far);
		
		result[0 + 3 * 4] = (left + right) / (left - right);
		result[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result[2 + 3 * 4] = (far + near) / (far - near);
		
		return result;
	}
	
	template <typename T>
	Matrix<T, 4> perspective(T fov, T aspectRatio, T near, T far)
	{
		Matrix<T, 4> result(1.0f);
		
		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;
		
		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);
		
		result[0 + 0 * 4] = a;
		result[1 + 1 * 4] = q;
		result[2 + 2 * 4] = b;
		result[3 + 2 * 4] = -1.0f;
		result[2 + 3 * 4] = c;
		
		return result;
	}
	
	template class Matrix<float, 2>;
	template class Matrix<float, 3>;
	template class Matrix<float, 4>;
	template class Matrix<double, 2>;
	template class Matrix<double, 3>;
	template class Matrix<double, 4>;
	
} }