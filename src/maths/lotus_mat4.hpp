#ifndef LOTUS_MAT4_HPP_INCLUDED
#define LOTUS_MAT4_HPP_INCLUDED

#include "lotus_vec3.hpp"
#include "lotus_vec4.hpp"
#include "lotus_quat.hpp"

namespace lotus { namespace maths {

	struct mat4
	{
		float elements[4 * 4];

		mat4();
		mat4(float diagonal);
		mat4(const quat &q);

		vec4 getColumn(int index)
		{
			index *= 4;
			return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
		}

		mat4 multiply(const mat4 &other) const;
		mat4 &operator*=(const mat4 &other);

		float &operator[](int index);

		friend mat4 operator*(const mat4 &left, const mat4 &right);

		static mat4 identity();

		static mat4 translation(const vec3 &translation);
		static mat4 rotation(float angle, const vec3 &axis);
		static mat4 rotation(const vec3 &f, const vec3 &u, const vec3 &r);
		static mat4 rotation(const quat &rotation);
		static mat4 scale(const vec3 &scale);

		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspective(float fov, float aspectRatio, float near, float far);
	};

} }

#endif