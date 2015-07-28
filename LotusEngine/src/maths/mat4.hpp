#ifndef LOTUS_MAT4_HPP_INCLUDED
#define LOTUS_MAT4_HPP_INCLUDED

#include "maths.hpp"

namespace lotus { namespace maths {

	class mat4
	{
	public:
		union {
			float elements[4 * 4];
			vec4 columns[4];
		};

		static mat4 identity();
		
		static mat4 translation(const vec3 &translation);
		static mat4 rotation(float angle, const vec3 &axis);
		static mat4 rotation(const vec3 &f, const vec3 &u, const vec3 &r);
		static mat4 rotation(const quat &rotation);
		static mat4 scale(const vec3 &scale);
		
		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspective(float fov, float aspectRatio, float near, float far);
		
		mat4();
		mat4(float diagonal);
		mat4(const quat &q);

		mat4 operator*(const mat4 &r) const;
		mat4 &operator*=(const mat4 &r);

		vec3 operator*(const vec3 &r) const;
		vec4 operator*(const vec4 &r) const;

		float &operator[](int index);
	};

} }

#endif
