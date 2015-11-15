#include "functions.hpp"

namespace lotus { namespace maths {

	template <typename T, unsigned int N>
	bool operator==(const mat<T, N> &l, const mat<T, N> &r)
	{
		for (unsigned int y = 0; y < N; y++)
		{
			for (unsigned int x = 0; x < N; x++)
			{
				if (l[x + y * N] != r[x + y * N]) return false;
			}
		}
		return true;
	}

	template <typename T, unsigned int N>
	bool operator!=(const mat<T, N> &l, const mat<T, N> &r)
	{
		return !l == r;
	}

	template <typename T, unsigned int N>
	mat<T, N> mul(const mat<T, N> &l, const mat<T, N> &r)
	{
		mat<T, N> result {};
		for (unsigned int y = 0; y < N; y++)
		{
			for (unsigned int x = 0; x < N; x++)
			{
				for (unsigned int i = 0; i < N; i++)
				{
					result.m[x + y * N] += l.m[x + i * N] * r.m[i + y * N];
				}
			}
		}
		return result;
	}

	template <typename T, unsigned int M_N, unsigned int V_N>
	vec<T, V_N> mul(const mat<T, M_N> &l, const vec<T, V_N> &r)
	{
		static_assert(M_N >= V_N, "mat size must be bigger than vec size.");
		vec<T, V_N> result {};
		for (unsigned int y = 0; y < V_N; y++)
		{
			for (unsigned int x = 0; x < M_N; x++)
			{
				result.v[y] += l.m[y + x * M_N] * (x < V_N ? r.v[x] : 1);
			}
		}
		return result;
	}

	template <typename T, unsigned int N>
	mat<T, N> mul(const mat<T, N> &l, T r)
	{
		mat<T, N> result {};
		for (unsigned int i = 0; i < N * N; i++)
		{
			result.m[i] = l.m[i] * r;
		}
		return result;
	}

	template <typename T, unsigned int N>
	mat<T, N> identity()
	{
		return mat<T, N>(1);
	}

	template <typename T, unsigned int N>
	mat<T, N> transpose(const mat<T, N> &m)
	{
		mat<T, N> result {};
		for (unsigned int y = 0; y < N; y++)
		{
			for (unsigned int x = 0; x < N; x++)
			{
				result.m[x + y * N] = m[y + x * N];
			}
		}
		return result;
	}

	template <typename T, unsigned int N>
	mat<T, N> translation(const vec<T, N - 1> &translation)
	{
		mat<T, N> result = identity<T, N>();
		for (unsigned int i = 0; i < N - 1; i++)
		{
			result.m[N * (N - 1) + i] = translation.v[i];
		}
		return result;
	}

	template <typename T, unsigned int N>
	mat<T, N> scale(const vec<T, N - 1> &scale)
	{
		mat<T, N> result = identity<T, N>();
		for (unsigned int i = 0; i < N - 1; i++)
		{
			result.m[i + i * N] = scale.v[i];
		}
		return result;
	}

	template <typename T, unsigned int N>
	mat<T, N> rotation(T angle)
	{
		mat<T, N> result = identity<T, N>();

		T sinAngle = sin<T>(angle);
		T cosAngle = cos<T>(angle);

		result.m[0 + 0 * N] = cosAngle;
		result.m[1 + 0 * N] = -sinAngle;
		result.m[0 + 1 * N] = sinAngle;
		result.m[1 + 1 * N] = cosAngle;

		return result;
	}

	template <typename T, unsigned int N>
	mat<T, N> rotation(T x, T y, T z)
	{
		mat<T, N> rx = identity<T, N>();
		mat<T, N> ry = identity<T, N>();
		mat<T, N> rz = identity<T, N>();

		const T sinx = sin<T>(x);
		const T cosx = cos<T>(x);
		const T siny = sin<T>(y);
		const T cosy = cos<T>(y);
		const T sinz = sin<T>(z);
		const T cosz = cos<T>(z);

		rx.m[1 + 1 * N] = cosx;
		rx.m[2 + 1 * N] = -sinx;
		rx.m[1 + 2 * N] = sinx;
		rx.m[2 + 2 * N] = cosx;

		ry.m[0 + 0 * N] = cosx;
		ry.m[2 + 0 * N] = -sinx;
		ry.m[0 + 2 * N] = sinx;
		ry.m[2 + 2 * N] = cosx;

		rz.m[0 + 0 * N] = cosx;
		rz.m[1 + 0 * N] = -sinx;
		rz.m[0 + 1 * N] = sinx;
		rz.m[1 + 1 * N] = cosx;

		return rz * ry * rx;
	}

	template <typename T, unsigned int N>
	mat<T, N> rotation(const vec<T, 3> &f, const vec<T, 3> &u, const vec<T, 3> &r)
	{
		mat<T, N> result = identity<T, N>();

		result.m[0 + 0 * N] = r.x;
		result.m[1 + 0 * N] = r.y;
		result.m[2 + 0 * N] = r.z;

		result.m[0 + 1 * N] = u.x;
		result.m[1 + 1 * N] = u.y;
		result.m[2 + 1 * N] = u.z;

		result.m[0 + 2 * N] = f.x;
		result.m[1 + 2 * N] = f.y;
		result.m[2 + 2 * N] = f.z;

		return result;
	}

	template <typename T, unsigned int N>
	mat<T, N> rotation(const quat<T> &rot)
	{
		const vec<T, 3> f = rotate(vec<T, 3>{0, 0, 1}, rot);
		const vec<T, 3> u = rotate(vec<T, 3>{0, 1, 0}, rot);
		const vec<T, 3> r = rotate(vec<T, 3>{1, 0, 0}, rot);

		return rotation<T, N>(f, u, r);
	}

	template <typename T, unsigned int N>
	mat<T, N> rotation(const vec<T, N> &axis, T angle)
	{
		mat<T, N> result = identity<T, N>();

		const T c = cos<T>(angle);
		const T s = sin<T>(angle);
		const T omc = (T) 1 - c;

		const T &x = axis.x;
		const T &y = axis.y;
		const T &z = axis.z;

		result.m[0 + 0 * 4] = x * omc + c;
		result.m[1 + 0 * 4] = y * x * omc + z * s;
		result.m[2 + 0 * 4] = x * z * omc - y * s;

		result.m[0 + 1 * 4] = x * y * omc - z * s;
		result.m[1 + 1 * 4] = y * omc + c;
		result.m[2 + 1 * 4] = y * z * omc + x * s;

		result.m[0 + 2 * 4] = x * z * omc + y * s;
		result.m[1 + 2 * 4] = y * z * omc - x * s;
		result.m[2 + 2 * 4] = z * omc + c;

		return result;
	}

	template <typename T>
	mat<T, 4> orthographic(T left, T right, T bottom, T top, T near, T far)
	{
		mat<T, 4> result {};

		result.m[0 + 0 * 4] = (T) 2 / (right - left);
		result.m[1 + 1 * 4] = (T) 2 / (top - bottom);
		result.m[2 + 2 * 4] = (T) 2 / (near - far);

		result.m[0 + 3 * 4] = (left + right) / (left - right);
		result.m[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.m[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	template <typename T>
	mat<T, 4> perspective(T fov, T aspectRatio, T near, T far)
	{
		mat<T, 4> result = identity<T, 4>();

		const T q = (T) 1 / tan(toRadians((T) 0.5 * fov));
		const T a = q / aspectRatio;

		const T b = (near + far) / (near - far);
		const T c = ((T) 2 * near * far) / (near - far);

		result.m[0 + 0 * 4] = a;
		result.m[1 + 1 * 4] = q;
		result.m[2 + 2 * 4] = b;
		result.m[3 + 2 * 4] = (T) -1;
		result.m[2 + 3 * 4] = c;

		return result;
	}


} }