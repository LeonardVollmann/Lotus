#include "lotus_quat.hpp"
#include "lotus_vec3.hpp"

#include <cmath>

namespace lotus { namespace maths { 

	quat::quat(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float quat::lengthSqr() const
	{
		return x * x + y * y + z * z + w * w;
	}

	float quat::length() const
	{
		return sqrtf(lengthSqr());
	}

	quat &quat::normalize()
	{
		const float length = this->length();

		x /= length;
		y /= length;
		z /= length;
		w /= length;

		return *this;
	}

	quat quat::conjugate() const
	{
		return quat(-x, -y, -z, w);
	}	

	quat operator*(const quat &left, const quat &right)
	{
		const float x = left.x * right.w + left.w * right.x + left.y * right.z - left.z * right.y;
		const float y = left.y * right.w + left.w * right.y + left.z * right.x - left.x * right.z;
		const float z = left.z * right.w + left.w * right.z + left.x * right.y - left.y * right.x;
		const float w = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;

		return quat(x, y, z, w);
	}

	quat operator*(const quat &left, const vec3 &right)
	{
		const float x =  left.w * right.x + left.y * right.z - left.z * right.y;
		const float y =  left.w * right.y + left.z * right.x - left.x * right.z;
		const float z =  left.w * right.z + left.x * right.y - left.y * right.x;
		const float w = -left.x * right.x - left.y * right.y - left.z * right.z;

		return quat(x, y, z, w);
	}

	quat &quat::multiply(const quat &other)
	{
		*this = (*this) * other;
		return *this;
	}

	quat &quat::operator*=(const quat &other)
	{
		return multiply(other);
	}

} }