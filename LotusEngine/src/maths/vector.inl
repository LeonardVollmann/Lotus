#include "vector.hpp"
#include "quaternion.hpp"
#include "mathsfunc.hpp"

namespace lotus { namespace maths {
	
	template <typename T, unsigned int N>
	Vector<T, N>::Vector(T t)
	{
		for (unsigned int i = 0; i < N; i++)
		{
			v[i] = t;
		}
	}
	
	template <typename T, unsigned int N>
	Vector<T, N>::Vector(T t[N])
	{
		memcpy(v, t, N * sizeof(T));
	}
	
	template <typename T, unsigned int N>
	bool operator==(const Vector<T, N> &l, const Vector<T, N> &r)
	{
		for (unsigned int i = 0; i < N; i++)
		{
			if (l.v[i] != r.v[i])
			{
				return false;
			}
		}
		
		return true;
	}
	
	template <typename T, unsigned int N>
	bool operator!=(const Vector<T, N> &l, const Vector<T, N> &r)
	{
		return !(l == r);
	}
	
	template <typename T, unsigned int N>
	T dot(const Vector<T, N> &l, const Vector<T, N> &r)
	{
		T result;
		for (unsigned int i = 0; i < N; i++)
		{
			result += l.v[i] * r.v[i];
		}
		
		return result;
	}
	
	template <typename T, unsigned int N>
	T lengthSquared(const Vector<T, N> &vec)
	{
		return dot(vec, vec);
	}
	
	template <typename T, unsigned int N>
	T length(const Vector<T, N> &vec)
	{
		return sqrt<T>(lengthSquared(vec));
	}
	
	template <typename T, unsigned int N>
	Vector<T, N> normalized(const Vector<T, N> &vec)
	{
		return vec / length(vec);
	}
	
	template <typename T, unsigned int N>
	Vector<T, N> add(const Vector<T, N> &l, const Vector<T, N> &r)
	{
		Vector<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] + r.v[i];
		}
		
		return result;
	}
	
	template <typename T, unsigned int N>
	Vector<T, N> sub(const Vector<T, N> &l, const Vector<T, N> &r)
	{
		Vector<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] - r.v[i];
		}
		
		return result;
	}
	
	template <typename T, unsigned int N>
	Vector<T, N> mul(const Vector<T, N> &l, const Vector<T, N> &r)
	{
		Vector<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] * r.v[i];
		}
		
		return result;
	}
	
	template <typename T, unsigned int N>
	Vector<T, N> div(const Vector<T, N> &l, const Vector<T, N> &r)
	{
		Vector<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] / r.v[i];
		}
		
		return result;
	}
	
	template <typename T, unsigned int N>
	Vector<T, N> add(const Vector<T, N> &l, T r)
	{
		Vector<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] + r;
		}
		
		return result;
	}
	
	template <typename T, unsigned int N>
	Vector<T, N> sub(const Vector<T, N> &l, T r)
	{
		Vector<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] - r;
		}
		
		return result;
	}
	
	template <typename T, unsigned int N>
	Vector<T, N> mul(const Vector<T, N> &l, T r)
	{
		Vector<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] * r;
		}
		
		return result;
	}
	
	template <typename T, unsigned int N>
	Vector<T, N> div(const Vector<T, N> &l, T r)
	{
		Vector<T, N> result;
		for (unsigned int i = 0; i < N; i++)
		{
			result.v[i] = l.v[i] / r;
		}
		
		return result;
	}
	
	template <typename T>
	Vector3<T> cross(const Vector3<T> &l, const Vector3<T> &r)
	{
		Vector3<T> result;
		result.x = l.y * r.z - l.z * r.y;
		result.y = l.z * r.x - l.x * r.z;
		result.z = l.x * r.y - l.y * r.x;
		
		return result;
	}
	
	template <typename T>
	Vector3<T> rotate(const Vector3<T> &v, const Quaternion<T> &q)
	{
		Quaternion<T> r = q * v * conjugate(q);
		return Vector3<T>(r.x, r.y, r.z);
	}
	
} }