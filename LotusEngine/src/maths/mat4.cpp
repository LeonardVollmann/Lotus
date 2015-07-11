#include "mat4.hpp"

#include <cmath>

namespace lotus { namespace maths {

	mat4 mat4::identity()
	{
		return mat4(1.0f);
	}

	mat4 mat4::translation(const vec3 &translation)
	{
		mat4 result(1.0f);
		
		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;
		
		return result;
	}

	mat4 mat4::rotation(float angle, const vec3 &axis)
	{
		mat4 result(1.0f);
		
		float c = cos(angle);
		float s = sin(angle);
		float omc = 1.0f - c;
		
		float x = axis.x;
		float y = axis.y;
		float z = axis.z;
		
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

	mat4 mat4::rotation(const vec3 &f, const vec3 &u, const vec3 &r)
	{
		mat4 result(1.0f);
		
		result[0 + 0 * 4] = r.x;
		result[1 + 0 * 4] = r.y;
		result[2 + 0 * 4] = r.z;
		
		result[0 + 1 * 4] = u.x;
		result[1 + 1 * 4] = u.y;
		result[2 + 1 * 4] = u.z;
		
		result[0 + 2 * 4] = f.x;
		result[1 + 2 * 4] = f.y;
		result[2 + 2 * 4] = f.z;
		
		return result;
	}

	mat4 mat4::rotation(const quat &rotation)
	{
		const vec3 f = vec3(0.0f, 0.0f, 1.0f).rotate(rotation);
		const vec3 r = vec3(1.0f, 0.0f, 0.0f).rotate(rotation);
		const vec3 u = vec3(0.0f, 1.0f, 0.0f).rotate(rotation);
		
		return mat4::rotation(f, u, r);
	}

	mat4 mat4::scale(const vec3 &scale)
	{
		mat4 result(1.0f);
		
		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;
		
		return result;
	}

	mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		mat4 result(1.0f);
		
		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		
		result.elements[2 + 2 * 4] = 2.0f / (near - far);
		
		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);
		
		return result;
	}

	mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
	{
		mat4 result(1.0f);
		
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

	mat4::mat4()
	{
		for (unsigned int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;
	}

	mat4::mat4(float diagonal)
	{
		for (unsigned int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	mat4::mat4(const quat &q)
	{
		(*this) = rotation(q.getForward(), q.getUp(), q.getRight());
	}

	mat4 mat4::operator*(const mat4 &r) const
	{
		mat4 result = *this;
		for (unsigned int y = 0; y < 4; y++)
		{
			for (unsigned int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (unsigned int i = 0; i < 4; i++)
				{
					sum += elements[x + i * 4] * r.elements[i + y * 4];
				}
				result.elements[x + y * 4] = sum;
			}
		}
		return result;
	}

	mat4& mat4::operator*=(const mat4& r)
	{
		*this = operator*(r);
		return *this;
	}

	float &mat4::operator[](int index)
	{
		return elements[index];
	}

} }