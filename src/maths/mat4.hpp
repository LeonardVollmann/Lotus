#ifndef MAT4_HPP
#define MAT4_HPP

#include "vec3.hpp"
#include "vec4.hpp"

namespace lotus { namespace maths {

	struct mat4
	{
		union
		{
			float elements[4 * 4];
			vec4 columns[4];
		};

		mat4();
		mat4(float diagonal);

		vec4 getColumn(int index)
		{
			index *= 4;
			return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
		}

		mat4& multiply(const mat4& other);
		mat4& operator*=(const mat4& other);

		friend mat4 operator*(mat4 left, const mat4& right);

		static mat4 identity();

		static mat4 translation(const vec3& translation);
		static mat4 rotation(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);

		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspective(float fov, float aspectRatio, float near, float far);
	};

} }

#endif