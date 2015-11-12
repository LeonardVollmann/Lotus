#ifndef LOTUS_MATHS_TYPES_HPP_INCLUDED
#define LOTUS_MATHS_TYPES_HPP_INCLUDED

namespace lotus { namespace maths {

	template <typename T, unsigned int N>
	struct vec {};

	template <typename T>
	struct vec<T, 2>
	{
		union
		{
			struct { T x, y; };
			struct { T r, g; };
			T v[2];
		};

		vec<T, 2>(T n = 0) :
			v{n, n} {}

		vec<T, 2>(T x, T y) :
			v{x, y} {}
	};

	template <typename T>
	struct vec<T, 3>
	{
		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
			union
			{
				vec<T, 2> xy;
				vec<T, 2> rg;
			};
			T v[3];
		};

		vec<T, 3>(T n = 0) :
			v{n, n, n} {}

		vec<T, 3>(T x, T y, T z) :
			v{x, y, z} {}
	};

	template <typename T>
	struct vec<T, 4>
	{
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			union
			{
				vec<T, 2> xy;
				vec<T, 2> rg;
				vec<T, 3> xyz;
				vec<T, 3> rgb;
			};
			T v[4];
		};

		vec<T, 4>(T n = 0) :
			v{n, n, n, n} {}

		vec<T, 4>(T x, T y, T z, T w) :
			v{x, y, z, w} {}
	};

	template <typename T>
	struct quat
	{
		union
		{
			T q[4];
			struct { T x, y, z, w; };
			vec<T, 3> xyz;
		};

		quat() :
			q{0, 0, 0, 1} {}

		quat(T x, T y, T z, T w) :
			q{x, y, z, w} {}
	};

	template <typename T, unsigned int N>
	struct mat
	{
		union
		{
			T m[N * N];
			vec<T, N> columns[N];
		};
	};

	typedef vec<float, 2>			vec2f;
	typedef vec<double, 2>			vec2d;
	typedef vec<char, 2>			vec2c;
	typedef vec<unsigned char, 2>	vec2uc;
	typedef vec<int, 2>				vec2i;
	typedef vec<unsigned int, 2>	vec2ui;

	typedef vec<float, 3>			vec3f;
	typedef vec<double, 3>			vec3d;
	typedef vec<char, 3>			vec3c;
	typedef vec<unsigned char, 3>	vec3uc;
	typedef vec<int, 3>				vec3i;
	typedef vec<unsigned int, 3>	vec3ui;

	typedef vec<float, 4>			vec4f;
	typedef vec<double, 4>			vec4d;
	typedef vec<char, 4>			vec4c;
	typedef vec<unsigned char, 4>	vec4uc;
	typedef vec<int, 4>				vec4i;
	typedef vec<unsigned int, 4>	vec4ui;

	typedef quat<float>				fquat;
	typedef quat<double>			dquat;

	typedef mat<float, 2>			mat2f;
	typedef mat<double, 2>			mat2d;
	typedef mat<char, 2>			mat2c;
	typedef mat<unsigned char, 2>	mat2uc;
	typedef mat<int, 2>				mat2i;
	typedef mat<unsigned int, 2>	mat2ui;

	typedef mat<float, 3>			mat3f;
	typedef mat<double, 3>			mat3d;
	typedef mat<char, 3>			mat3c;
	typedef mat<unsigned char, 3>	mat3uc;
	typedef mat<int, 3>				mat3i;
	typedef mat<unsigned int, 3>	mat3ui;

	typedef mat<float, 4>			mat4f;
	typedef mat<double, 4>			mat4d;
	typedef mat<char, 4>			mat4c;
	typedef mat<unsigned char, 4>	mat4uc;
	typedef mat<int, 4>				mat4i;
	typedef mat<unsigned int, 4>	mat4ui;

} }

#endif