#ifndef LOTUS_MATHS_HPP_INCLUDED
#define LOTUS_MATHS_HPP_INCLUDED

#include <cmath>
#include <cstring>

namespace lotus { namespace maths {
	
	template <typename T, unsigned int N>
	struct Vector {};
	
	template <typename T>
	struct Vector2;
	
	template <typename T>
	struct Vector3;
	
	template <typename T>
	struct Vector3;
	
	template <typename T>
	struct Quaternion;
	
	template <typename T, unsigned int N>
	struct Matrix;

	template <typename T>
	T sin(T n);
	template <>
	inline float sin(float f) { return sinf(f); }
	template <>
	inline double sin(double d) { return sin(d); }
	
	template <typename T>
	T cos(T n);
	template <>
	inline float cos(float f) { return cosf(f); }
	template <>
	inline double cos(double d) { return cos(d); }
	
	template <typename T>
	T sqrt(T n);
	template <>
	inline float sqrt(float f) { return sqrtf(f); }
	template <>
	inline double sqrt(double d) { return sqrt(d); }
	
	template <typename T>
	inline T toRadians(T deg)
	{
		return deg / T(180) * M_PI;
	}
	
	template <typename T>
	inline T toDegrees(T rad)
	{
		return rad / M_PI * T(180);
	}
	
	template <typename T>
	struct Vector2 : Vector<T, 2>
	{
		Vector2(T t = 0) :
			v{t} {}

		Vector2(T x, T y) :
			x(x),
			y(y) {}
		
		Vector2(T t[2])
		{
			memcpy(v, t, 2 * sizeof(T));
		}
		
		union
		{
			T v[2];
			struct { T x, y; };
			struct { T r, g; };
		};
	};
	
	template <typename T>
	inline bool operator==(const Vector2<T> &l, const Vector2<T> &r)
	{
		return (l.x == r.x) && (l.y == r.y);
	}
	
	template <typename T>
	inline bool operator!=(const Vector2<T> &l, const Vector2<T> &r)
	{
		return !(l == r);
	}
	
	template <typename T>
	inline T lengthSquared(const Vector2<T> &vec)
	{
		return vec.x * vec.x + vec.y * vec.y;
	}
	
	template <typename T>
	inline T length(const Vector2<T> &vec)
	{
		return sqrtf(lengthSquared(vec));
	}
	
	template <typename T>
	inline Vector2<T> normalize(const Vector2<T> &vec)
	{
		Vector2<T> result(vec);
		result /= length(result);
		return result;
	}
	
	template <typename T>
	inline Vector2<T> add(const Vector2<T> &l, const Vector2<T> &r)
	{
		Vector2<T> result;
		result.x = l.x + r.x;
		result.y = l.y + r.y;
		return result;
	}
	
	template <typename T>
	inline Vector2<T> sub(const Vector2<T> &l, const Vector2<T> &r)
	{
		Vector2<T> result;
		result.x = l.x - r.x;
		result.y = l.y - r.y;
		return result;
	}
	
	template <typename T>
	inline Vector2<T> mul(const Vector2<T> &l, const Vector2<T> &r)
	{
		Vector2<T> result;
		result.x = l.x * r.x;
		result.y = l.y * r.y;
		return result;
	}
	
	template <typename T>
	inline Vector2<T> div(const Vector2<T> &l, const Vector2<T> &r)
	{
		Vector2<T> result;
		result.x = l.x / r.x;
		result.y = l.y / r.y;
		return result;
	}
	
	template <typename T>
	inline Vector2<T> mul(const Vector2<T> &l, T r)
	{
		Vector2<T> result(l);
		result.x *= r;
		result.y *= r;
		return result;
	}
	
	template <typename T>
	inline Vector2<T> div(const Vector2<T> &l, T r)
	{
		Vector2<T> result(l);
		result.x /= r;
		result.y /= r;
		return result;
	}
	
	template <typename T>
	inline Vector2<T> operator+(const Vector2<T> &l, const Vector2<T> &r) { return add(l, r); }
	template <typename T>
	inline Vector2<T> operator-(const Vector2<T> &l, const Vector2<T> &r) { return sub(l, r); }
	template <typename T>
	inline Vector2<T> operator*(const Vector2<T> &l, const Vector2<T> &r) { return mul(l, r); }
	template <typename T>
	inline Vector2<T> operator/(const Vector2<T> &l, const Vector2<T> &r) { return div(l, r); }
	
	template <typename T>
	inline Vector2<T> operator*(const Vector2<T> &l, T r) { return mul(l, r); }
	template <typename T>
	inline Vector2<T> operator/(const Vector2<T> &l, T r) { return div(l, r); }
	
	template <typename T>
	inline void operator+=(Vector2<T> &l, const Vector2<T> &r) { l = l + r; }
	template <typename T>
	inline void operator-=(Vector2<T> &l, const Vector2<T> &r) { l = l - r; }
	template <typename T>
	inline void operator*=(Vector2<T> &l, const Vector2<T> &r) { l = l * r; }
	template <typename T>
	inline void operator/=(Vector2<T> &l, const Vector2<T> &r) { l = l / r; }
	
	typedef Vector2<float>			Vector2f;
	typedef Vector2<double>			Vector2d;
	typedef Vector2<int>			Vector2i;
	typedef Vector2<unsigned int>	Vector2ui;
	
	template <typename T>
	struct Vector3 : Vector<T, 3>
	{
		Vector3(T t = 0) :
			v{t} {}
		
		Vector3(T x, T y, T z) :
			x(x),
			y(y),
			z(z) {}
		
		Vector3(T t[3])
		{
			memcpy(v, t, 3 * sizeof(T));
		}
		
		union
		{
			T v[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};
	};
	
	template <typename T>
	inline bool operator==(const Vector3<T> &l, const Vector3<T> &r)
	{
		return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
	}
	
	template <typename T>
	inline bool operator!=(const Vector3<T> &l, const Vector3<T> &r)
	{
		return !(l == r);
	}
	
	template <typename T>
	inline T lengthSquared(const Vector3<T> &vec)
	{
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	}
	
	template <typename T>
	inline T length(const Vector3<T> &vec)
	{
		return sqrtf(lengthSquared(vec));
	}
	
	template <typename T>
	inline Vector3<T> normalize(const Vector3<T> &vec)
	{
		Vector3<T> result;
		result = vec / length(vec);
		return result;
	}
	
	template <typename T>
	inline Vector3<T> add(const Vector3<T> &l, const Vector3<T> &r)
	{
		Vector3<T> result;
		result.x = l.x + r.x;
		result.y = l.y + r.y;
		result.z = l.z + r.z;
		return result;
	}
	
	template <typename T>
	inline Vector3<T> sub(const Vector3<T> &l, const Vector3<T> &r)
	{
		Vector3<T> result;
		result.x = l.x - r.x;
		result.y = l.y - r.y;
		result.z = l.z - r.z;
		return result;
	}
	
	template <typename T>
	inline Vector3<T> mul(const Vector3<T> &l, const Vector3<T> &r)
	{
		Vector3<T> result;
		result.x = l.x * r.x;
		result.y = l.y * r.y;
		result.z = l.z * r.z;
		return result;
	}
	
	template <typename T>
	inline Vector3<T> div(const Vector3<T> &l, const Vector3<T> &r)
	{
		Vector3<T> result;
		result.x = l.x / r.x;
		result.y = l.y / r.y;
		result.z = l.z / r.z;
		return result;
	}
	
	template <typename T>
	inline Vector3<T> mul(const Vector3<T> &l, T r)
	{
		Vector3<T> result(l);
		result.x *= r;
		result.y *= r;
		result.z *= r;
		return result;
	}
	
	template <typename T>
	inline Vector3<T> div(const Vector3<T> &l, T r)
	{
		Vector3<T> result(l);
		result.x /= r;
		result.y /= r;
		result.z /= r;
		return result;
	}
	
	template <typename T>
	inline Vector3<T> cross(const Vector3<T> &l, const Vector3<T> &r)
	{
		Vector3<T> result;
		result.x = l.y * r.z - l.z * r.y;
		result.y = l.z * r.x - l.x * r.z;
		result.z = l.x * r.y - l.y * r.x;
		
		return result;
	}
	
	template <typename T>
	inline Vector3<T> rotate(const Vector3<T> &v, const Quaternion<T> &q)
	{
		Quaternion<T> r = q * v * conjugate(q);
		return Vector3<T>(r.x, r.y, r.z);
	}
	
	template <typename T>
	inline Vector3<T> operator+(const Vector3<T> &l, const Vector3<T> &r) { return add(l, r); }
	template <typename T>
	inline Vector3<T> operator-(const Vector3<T> &l, const Vector3<T> &r) { return sub(l, r); }
	template <typename T>
	inline Vector3<T> operator*(const Vector3<T> &l, const Vector3<T> &r) { return mul(l, r); }
	template <typename T>
	inline Vector3<T> operator/(const Vector3<T> &l, const Vector3<T> &r) { return div(l, r); }
	
	template <typename T>
	inline Vector3<T> operator*(const Vector3<T> &l, T r) { return mul(l, r); }
	template <typename T>
	inline Vector3<T> operator/(const Vector3<T> &l, T r) { return div(l, r); }
	
	template <typename T>
	inline void operator+=(Vector3<T> &l, const Vector3<T> &r) { l = l + r; }
	template <typename T>
	inline void operator-=(Vector3<T> &l, const Vector3<T> &r) { l = l - r; }
	template <typename T>
	inline void operator*=(Vector3<T> &l, const Vector3<T> &r) { l = l * r; }
	template <typename T>
	inline void operator/=(Vector3<T> &l, const Vector3<T> &r) { l = l / r; }
	
	typedef Vector3<float>			Vector3f;
	typedef Vector3<double>			Vector3d;
	typedef Vector3<int>			Vector3i;
	typedef Vector3<unsigned int>	Vector3ui;
	
	template <typename T>
	struct Vector4 : Vector<T, 4>
	{
		Vector4(T t = 0) :
			v{t} {}
		
		Vector4(T x, T y, T z, T w) :
			x(x),
			y(y),
			z(z),
			w(w) {}
		
		Vector4(T t[4])
		{
			memcpy(v, t, 4 * sizeof(T));
		}
		
		union
		{
			T v[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};
	};
	
	template <typename T>
	inline bool operator==(const Vector4<T> &l, const Vector4<T> &r)
	{
		return (l.x == r.x) && (l.y == r.y) && (l.z == r.z) && (l.w == r.w);
	}
	
	template <typename T>
	inline bool operator!=(const Vector4<T> &l, const Vector4<T> &r)
	{
		return !(l == r);
	}
	
	template <typename T>
	inline T lengthSquared(const Vector4<T> &vec)
	{
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
	}
	
	template <typename T>
	inline T length(const Vector4<T> &vec)
	{
		return sqrt<T>(lengthSquared(vec));
	}
	
	template <typename T>
	inline Vector4<T> normalize(const Vector4<T> &vec)
	{
		Vector4<T> result(vec);
		result /= length(result);
		return result;
	}
	
	template <typename T>
	inline Vector4<T> add(const Vector4<T> &l, const Vector4<T> &r)
	{
		Vector4<T> result;
		result.x = l.x + r.x;
		result.y = l.y + r.y;
		result.z = l.z + r.z;
		result.w = l.w + r.w;
		return result;
	}
	
	template <typename T>
	inline Vector4<T> sub(const Vector4<T> &l, const Vector4<T> &r)
	{
		Vector4<T> result;
		result.x = l.x - r.x;
		result.y = l.y - r.y;
		result.z = l.z - r.z;
		result.w = l.w - r.w;
		return result;
	}
	
	template <typename T>
	inline Vector4<T> mul(const Vector4<T> &l, const Vector4<T> &r)
	{
		Vector4<T> result;
		result.x = l.x * r.x;
		result.y = l.y * r.y;
		result.z = l.z * r.z;
		result.w = l.w * r.w;
		return result;
	}
	
	template <typename T>
	inline Vector4<T> div(const Vector4<T> &l, const Vector4<T> &r)
	{
		Vector4<T> result;
		result.x = l.x / r.x;
		result.y = l.y / r.y;
		result.z = l.z / r.z;
		result.w = l.w / r.w;
		return result;
	}
	
	template <typename T>
	inline Vector4<T> mul(const Vector4<T> &l, T r)
	{
		Vector4<T> result(l);
		result.x *= r;
		result.y *= r;
		result.z *= r;
		result.w *= r;
		return result;
	}
	
	template <typename T>
	inline Vector4<T> div(const Vector4<T> &l, T r)
	{
		Vector4<T> result(l);
		result.x /= r;
		result.y /= r;
		result.z /= r;
		result.w /= r;
		return result;
	}
	
	template <typename T>
	inline Vector4<T> operator+(const Vector4<T> &l, const Vector4<T> &r) { return add(l, r); }
	template <typename T>
	inline Vector4<T> operator-(const Vector4<T> &l, const Vector4<T> &r) { return sub(l, r); }
	template <typename T>
	inline Vector4<T> operator*(const Vector4<T> &l, const Vector4<T> &r) { return mul(l, r); }
	template <typename T>
	inline Vector4<T> operator/(const Vector4<T> &l, const Vector4<T> &r) { return div(l, r); }
	
	template <typename T>
	inline Vector4<T> operator*(const Vector4<T> &l, T r) { return mul(l, r); }
	template <typename T>
	inline Vector4<T> operator/(const Vector4<T> &l, T r) { return div(l, r); }
	
	template <typename T>
	inline void operator+=(Vector4<T> &l, const Vector4<T> &r) { l = l + r; }
	template <typename T>
	inline void operator-=(Vector4<T> &l, const Vector4<T> &r) { l = l - r; }
	template <typename T>
	inline void operator*=(Vector4<T> &l, const Vector4<T> &r) { l = l * r; }
	template <typename T>
	inline void operator/=(Vector4<T> &l, const Vector4<T> &r) { l = l / r; }
	
	typedef Vector4<float>			Vector4f;
	typedef Vector4<double>			Vector4d;
	typedef Vector4<int>			Vector4i;
	typedef Vector4<unsigned int>	Vector4ui;
	
	template <typename T>
	struct Quaternion
	{
		Quaternion(T x = (T) 0, T y = (T) 0, T z = (T) 0, T w = (T) 1) :
			x(x),
			y(y),
			z(z),
			w(w) {}
		
		Quaternion(const Vector3<T> &axis, T angle)
		{
			const T sinHalfAngle = sin<T>(angle / (T) 2);
			const T cosHalfAngle = cos<T>(angle / (T) 2);
			
			x = axis.x * sinHalfAngle;
			y = axis.y * sinHalfAngle;
			z = axis.z * sinHalfAngle;
			w = cosHalfAngle;
		}
		
		T x, y, z, w;
	};
	
	template <typename T>
	inline bool operator==(const Quaternion<T> &l, const Quaternion<T> &r)
	{
		return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
	}
	
	template <typename T>
	inline bool operator!=(const Quaternion<T> &l, const Quaternion<T> &r)
	{
		return !l == r;
	}
	
	template <typename T>
	inline T lengthSquared(const Quaternion<T> &q)
	{
		return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	}
	
	template <typename T>
	inline T length(const Quaternion<T> &q)
	{
		return sqrt<T>(lengthSquared(q));
	}
	
	template <typename T>
	inline Quaternion<T> normalize(const Quaternion<T> &q)
	{
		const T l = length(q);
		return Quaternion<T>(q.x / l, q.y / l, q.z / l, q.w / l);
	}
	
	template <typename T>
	inline Quaternion<T> conjugate(const Quaternion<T> &q)
	{
		return Quaternion<T>(-q.x, -q.y, -q.z, q.w);
	}

	
	template <typename T>
	inline Quaternion<T> mul(const Quaternion<T> &l, T r)
	{
		Quaternion<T> result;
		result.x = l.x * r;
		result.y = l.y * r;
		result.z = l.z * r;
		result.w = l.w * r;
		
		return result;
	}
	
	template <typename T>
	inline Quaternion<T> mul(const Quaternion<T> &l, const Quaternion<T> &r)
	{
		const T w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;
		const T x = l.x * r.w + l.w * r.x + l.y * r.z - l.z * r.y;
		const T y = l.y * r.w + l.w * r.y + l.z * r.x - l.x * r.z;
		const T z = l.z * r.w + l.w * r.z + l.x * r.y - l.y * r.x;
		
		return Quaternion<T>(x, y, z, w);
	}
	
	template <typename T>
	inline Quaternion<T> mul(const Quaternion<T> &l, const Vector3<T> &r)
	{
		const float w = -l.x * r.x - l.y * r.y - l.z * r.z;
		const float x =  l.w * r.x + l.y * r.z - l.z * r.y;
		const float y =  l.w * r.y + l.z * r.x - l.x * r.z;
		const float z =  l.w * r.z + l.x * r.y - l.y * r.x;
		
		return Quaternion<T>(x, y, z, w);
	}

	template <typename T>
	inline Quaternion<T> operator*(const Quaternion<T> &l, T r) { return mul(l, r); }
	template <typename T>
	inline Quaternion<T> operator*(const Quaternion<T> &l, const Quaternion<T> &r) { return mul(l, r); }
	template <typename T>
	inline Quaternion<T> operator*(const Quaternion<T> &l, const Vector3<T> &r) { return mul(l, r); }
	
	template <typename T>
	inline void operator*=(Quaternion<T> &l, T r) { l = l * r; }
	template <typename T>
	inline void operator*=(Quaternion<T> &l, const Quaternion<T> &r) { l = l * r; }
	template <typename T>
	inline void operator*=(Quaternion<T> &l, const Vector3<T> &r) { l = l * r; }
	
	template <typename T>
	inline Vector3<T> getForward(const Quaternion<T> &q)	{ return rotate(Vector3<T>(0, 0, -1), q); }
	template <typename T>
	inline Vector3<T> getBack(const Quaternion<T> &q)		{ return rotate(Vector3<T>(0, 0, 1), q); }
	template <typename T>
	inline Vector3<T> getUp(const Quaternion<T> &q)			{ return rotate(Vector3<T>(0, 1, 0), q); }
	template <typename T>
	inline Vector3<T> getDown(const Quaternion<T> &q)		{ return rotate(Vector3<T>(0, -1, 0), q); }
	template <typename T>
	inline Vector3<T> getRight(const Quaternion<T> &q)		{ return rotate(Vector3<T>(1, 0, 0), q); }
	template <typename T>
	inline Vector3<T> getLeft(const Quaternion<T> &q)		{ return rotate(Vector3<T>(-1, 0, 0), q); }
	
	typedef Quaternion<float> QuaternionF;
	typedef Quaternion<double> QuaternionD;
	
	template <typename T, unsigned int N>
	struct Matrix
	{
		Matrix(T diagonal = 0)
		{
			for (unsigned int y = 0; y < N; y++)
			{
				for (unsigned int x = 0; x < N; x++)
				{
					if (x == y) m[x + y * N] = diagonal;
					else m[x + y * N] = (T) 0;
				}
			}
		}

		T m[N * N];
	};
	
	template <typename T, unsigned int N>
	inline bool operator==(const Matrix<T, N> &l, const Matrix<T, N> &r)
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
	inline bool operator!=(const Matrix<T, N> &l, const Matrix<T, N> &r)
	{
		return !l == r;
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> mul(const Matrix<T, N> &l, const Matrix<T, N> &r)
	{
		Matrix<T, N> result;
		for (unsigned int y = 0; y < N; y++)
		{
			for (unsigned int x = 0; x < N; x++)
			{
				result.m[x + y * N] = 0;
				for (unsigned int i = 0; i < N; i++)
				{
					result.m[x + y * N] += l.m[x + i * N] * r.m[i + y * N];
				}
			}
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> mul(const Matrix<T, N> &l, T r)
	{
		Matrix<T, N> result;
		for (unsigned int i = 0; i < N * N; i++)
		{
			result.m[i] = l.m[i] * r;
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> operator*(const Matrix<T, N> &l, const Matrix<T, N> &r) { return mul(l, r); }
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> operator*(const Matrix<T, N> &l, T r) { return mul(l, r); }
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> identity()
	{
		return Matrix<T, N>((T) 1);
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> transposed(const Matrix<T, N> &m)
	{
		Matrix<T, N> result;
		for (unsigned int y = 0; y < N; y++)
		{
			for (unsigned int x = 0; x < N; x++)
			{
				result[x + y * N] = m[y + x * N];
			}
		}
		return result;
	}

	template <typename T>
	inline Matrix<T, 3> translation(const Vector2<T> &translation)
	{
		Matrix<T, 3> result(1);
		for (unsigned int i = 0; i < 2; i++)
		{
			result.m[5] = translation.v[i];
		}
		return result;
	}
	
	template <typename T>
	inline Matrix<T, 4> translation(const Vector3<T> &translation)
	{
		Matrix<T, 4> result(1);
		for (unsigned int i = 0; i < 3; i++)
		{
			result.m[12 + i] = translation.v[i];
		}
		return result;
	}
	
	template <typename T>
	inline Matrix<T, 3> scale(const Vector2<T> &scale)
	{
		Matrix<T, 3> result(1);
		for (unsigned int i = 0; i < 2; i++)
		{
			result.m[i + i * 3] = scale.v[i];
		}
		return result;
	}
	
	template <typename T>
	inline Matrix<T, 4> scale(const Vector3<T> &scale)
	{
		Matrix<T, 4> result(1);
		for (unsigned int i = 0; i < 3; i++)
		{
			result.m[i + i * 4] = scale.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> rotation(T angle)
	{
		Matrix<T, N> result(1);
		
		T sinAngle = sin<T>(angle);
		T cosAngle = cos<T>(angle);
		
		result[0 + 0 * N] = cosAngle;
		result[1 + 0 * N] = -sinAngle;
		result[0 + 1 * N] = sinAngle;
		result[1 + 1 * N] = cosAngle;
		
		return result;
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> rotation(T x, T y, T z)
	{
		Matrix<T, N> rx(1);
		Matrix<T, N> ry(1);
		Matrix<T, N> rz(1);
		
		const T sinx = sin<T>(x);
		const T cosx = cos<T>(x);
		const T siny = sin<T>(y);
		const T cosy = cos<T>(y);
		const T sinz = sin<T>(z);
		const T cosz = cos<T>(z);
		
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
	inline Matrix<T, N> rotation(const Vector3<T> &f, const Vector3<T> &u, const Vector3<T> &r)
	{
		Matrix<T, N> result(1);
		
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
	inline Matrix<T, N> rotation(const Quaternion<T> &rot)
	{
		const Vector3<T> f = rotate(Vector3<T>(0.0f, 0.0f, 1.0f), rot);
		const Vector3<T> u = rotate(Vector3<T>(0.0f, 1.0f, 0.0f), rot);
		const Vector3<T> r = rotate(Vector3<T>(1.0f, 0.0f, 0.0f), rot);
		
		return rotation<T, N>(f, u, r);
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> rotation(const Vector<T, N> &axis, T angle)
	{
		Matrix<T, N> result(1);
		
		const T c = cos<T>(angle);
		const T s = sin<T>(angle);
		const T omc = (T) 1 - c;
		
		const T &x = axis.x;
		const T &y = axis.y;
		const T &z = axis.z;
		
		result[0 + 0 * 4] = x * omc + c;
		result[1 + 0 * 4] = y * x * omc + z * s;
		result[2 + 0 * 4] = x * z * omc - y * s;
		
		result[0 + 1 * 4] = x * y * omc - z * s;
		result[1 + 1 * 4] = y * omc + c;
		result[2 + 1 * 4] = y * z * omc + x * s;
		
		result[0 + 2 * 4] = x * z * omc + y * s;
		result[1 + 2 * 4] = y * z * omc - x * s;
		result[2 + 2 * 4] = z * omc + c;
		
		return result;
	}
	
	template <typename T>
	inline Matrix<T, 4> orthographic(T left, T right, T bottom, T top, T near, T far)
	{
		Matrix<T, 4> result;
		
		result[0 + 0 * 4] = (T) 2 / (right - left);
		result[1 + 1 * 4] = (T) 2 / (top - bottom);
		result[2 + 2 * 4] = (T) 2 / (near - far);
		
		result[0 + 3 * 4] = (left + right) / (left - right);
		result[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result[2 + 3 * 4] = (far + near) / (far - near);
		
		return result;
	}
	
	template <typename T>
	inline Matrix<T, 4> perspective(T fov, T aspectRatio, T near, T far)
	{
		Matrix<T, 4> result(1);
		
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
	
	typedef Matrix<float, 2> Matrix2f;
	typedef Matrix<float, 3> Matrix3f;
	typedef Matrix<float, 4> Matrix4f;
	typedef Matrix<double, 2> Matrix2d;
	typedef Matrix<double, 3> Matrix3d;
	typedef Matrix<double, 4> Matrix4d;
	
} }

#endif