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
		union
		{
			T v[2];
			struct { T x, y; };
			struct { T r, g; };
		};
		
		Vector2(T t = 0) :
			v{t} {}

		Vector2(T x, T y) :
			x(x),
			y(y) {}
		
		Vector2(T t[2])
		{
			memcpy(v, t, 2 * sizeof(T));
		}
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
	inline Vector2<T> normalized(const Vector2<T> &vec)
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
		union
		{
			T v[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};
		
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
	inline Vector3<T> normalized(const Vector3<T> &vec)
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
		union
		{
			T v[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};
		
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
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	}
	
	template <typename T>
	inline T length(const Vector4<T> &vec)
	{
		return sqrtf(lengthSquared(vec));
	}
	
	template <typename T>
	inline Vector4<T> normalized(const Vector4<T> &vec)
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
		T x;
		T y;
		T z;
		T w;
		
		Quaternion(T x = (T) 0, T y = (T) 0, T z = (T) 0, T w = (T) 1) :
			x(x),
			y(y),
			z(z),
			w(w) {}
		
		Quaternion(const Vector3<T> &axis, T angle)
		{
			const T sinHalfAngle = (T) sinf(angle / (T) 2);
			const T cosHalfAngle = (T) cosf(angle / (T) 2);
			
			x = axis.x * sinHalfAngle;
			y = axis.y * sinHalfAngle;
			z = axis.z * sinHalfAngle;
			w = cosHalfAngle;
		}
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
	inline Quaternion<T> normalized(const Quaternion<T> &q)
	{
		return Quaternion<T>(q) * ((T) 1 / length(q));
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
		const T x = l.x * r.w + l.w * r.x + l.y * r.z - l.z * r.y;
		const T y = l.y * r.w + l.w * r.y + l.z * r.x - l.x * r.z;
		const T z = l.z * r.w + l.w * r.z + l.x * r.y - l.y * r.x;
		const T w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;
		
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
	inline Vector3<T> getForward(const Quaternion<T> &q)	{ return rotate(Vector3<T>(0, 0, 1), q); }
	template <typename T>
	inline Vector3<T> getBack(const Quaternion<T> &q)		{ return rotate(Vector3<T>(0, 0, -1), q); }
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
		T elements[N * N];
		
		Matrix(T diagonal = 0)
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
	};
	
	template <typename T, unsigned int N>
	inline bool operator==(const Matrix<T, N> &l, const Matrix<T, N> &r)
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
	inline bool operator!=(const Matrix<T, N> &l, const Matrix<T, N> &r)
	{
		return !l == r;
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> mul(const Matrix<T, N> &l, const Matrix<T, N> &r)
	{
		Matrix<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int j = 0; j < N; j++)
			{
				T n;
				for (unsigned int k = 0; k < N; k++)
				{
					n +=  l.elements[i + k * N] * r.elements[k + j * N];
				}
				result.elements[i + j * N] = n;
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
			result[i] = l[i] * r;
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
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int j = 0; j < N; j++)
			{
				result[j + i * N] = m[i + j * N];
			}
		}
		return result;
	}
	
//	template <typename T, unsigned int N>
//	Matrix<T, N> translation(const Vector<T, N - 1> &translation);

	template <typename T>
	inline Matrix<T, 3> translation(const Vector2<T> &translation)
	{
		Matrix<T, 3> result;
		for (unsigned int i = 0; i < 3 - 1; i++)
		{
			result.elements[3 - 1 + i * 3] = translation.v[i];
		}
		return result;
	}
	
	template <typename T>
	inline Matrix<T, 4> translation(const Vector3<T> &translation)
	{
		Matrix<T, 4> result;
		for (unsigned int i = 0; i < 4 - 1; i++)
		{
			result.elements[4 - 1 + i * 4] = translation.v[i];
		}
		return result;
	}
	
//	template <typename T, unsigned int N>
//	Matrix<T, N> scale(const Vector<T, N - 1> &scale);
	
	template <typename T>
	inline Matrix<T, 3> scale(const Vector2<T> &scale)
	{
		Matrix<T, 3> result;
		for (unsigned int i = 0; i < 3 - 1; i++)
		{
			result.elements[i * (3 + 1)] = scale.v[i];
		}
		return result;
	}
	
	template <typename T>
	inline Matrix<T, 4> scale(const Vector3<T> &scale)
	{
		Matrix<T, 4> result;
		for (unsigned int i = 0; i < 4 - 1; i++)
		{
			result.elements[i * (4 + 1)] = scale.v[i];
		}
		return result;
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> rotation(T angle)
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
	inline Matrix<T, N> rotation(T x, T y, T z)
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
	inline Matrix<T, N> rotation(const Vector3<T> &f, const Vector3<T> &u, const Vector3<T> &r)
	{
		Matrix<T, N> result(1);
		
		result.elements[0 + 0 * N] = r.x;
		result.elements[1 + 0 * N] = r.y;
		result.elements[2 + 0 * N] = r.z;
		result.elements[0 + 1 * N] = u.x;
		result.elements[1 + 1 * N] = u.y;
		result.elements[2 + 1 * N] = u.z;
		result.elements[0 + 2 * N] = f.x;
		result.elements[1 + 2 * N] = f.y;
		result.elements[2 + 2 * N] = f.z;
		
		return result;
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> rotation(const Quaternion<T> &rot)
	{
		T f[3] = { 2 * (rot.x * rot.z - rot.w * rot.y), 2.0f * (rot.y * rot.z + rot.w * rot.x), 1.0f - 2.0f * (rot.x * rot.x + rot.y * rot.y) };
		T u[3] = { 2 * (rot.x * rot.y + rot.w * rot.z), 1.0f - 2.0f * (rot.x * rot.x + rot.z * rot.z), 2.0f * (rot.y * rot.z - rot.w * rot.x) };
		T r[3] = { 1 - 2.0f * (rot.y * rot.y + rot.z * rot.z), 2.0f * (rot.x * rot.y - rot.w * rot.z), 2.0f * (rot.x * rot.z + rot.w * rot.y) };
		
		return rotation<T, N>(Vector3<T>(f), Vector3<T>(u), Vector3<T>(r));
	}
	
	template <typename T, unsigned int N>
	inline Matrix<T, N> rotation(const Vector<T, N> &axis, T angle)
	{
		return rotation(Quaternion<T>(axis, angle));
	}
	
	template <typename T>
	inline Matrix<T, 4> orthographic(T left, T right, T bottom, T top, T near, T far)
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
	inline Matrix<T, 4> perspective(T fov, T aspectRatio, T near, T far)
	{
		Matrix<T, 4> result(1.0f);
		
		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;
		
		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);
		
		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = c;
		
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