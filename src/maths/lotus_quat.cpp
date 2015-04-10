#include "lotus_quat.hpp"
#include "lotus_vec3.hpp"

#include <cmath>

quat::quat()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}

quat::quat(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

quat::quat(float angle, const vec3 &axis)
{
	const float sinHalfAngle = sinf(angle / 2);
	const float cosHalfAngle = cosf(angle / 2);
	
	x = axis.x * sinHalfAngle;
	y = axis.y * sinHalfAngle;
	z = axis.z * sinHalfAngle;
	w = cosHalfAngle;
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
	const float w_ = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;
	const float x_ = left.x * right.w + left.w * right.x + left.y * right.z - left.z * right.y;
	const float y_ = left.y * right.w + left.w * right.y + left.z * right.x - left.x * right.z;
	const float z_ = left.z * right.w + left.w * right.z + left.x * right.y - left.y * right.x;
	
	return quat(x_, y_, z_, w_);
}

quat operator*(const quat &left, const vec3 &right)
{
	const float w_ = -left.x * right.x - left.y * right.y - left.z * right.z;
	const float x_ =  left.w * right.x + left.y * right.z - left.z * right.y;
	const float y_ =  left.w * right.y + left.z * right.x - left.x * right.z;
	const float z_ =  left.w * right.z + left.x * right.y - left.y * right.x;
	
	return quat(x_, y_, z_, w_);
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

vec3 quat::getForward() const
{
	return vec3(0.0f, 0.0f, 1.0f).rotate(*this);
}

vec3 quat::getBack() const
{
	return vec3(0.0f, 0.0f, -1.0f).rotate(*this);
}

vec3 quat::getUp() const
{
	return vec3(0.0f, 1.0f, 0.0f).rotate(*this);
}

vec3 quat::getDown() const
{
	return vec3(0.0f, -1.0f, 0.0f).rotate(*this);
}

vec3 quat::getRight() const
{
	return vec3(1.0f, 0.0f, 0.0f).rotate(*this);
}

vec3 quat::getLeft() const
{
	return vec3(-1.0f, 0.0f, 0.0f).rotate(*this);
}