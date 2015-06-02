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

quat quat::operator*(const quat &r) const
{
	const float w_ = w * r.w - x * r.x - y * r.y - z * r.z;
	const float x_ = x * r.w + w * r.x + y * r.z - z * r.y;
	const float y_ = y * r.w + w * r.y + z * r.x - x * r.z;
	const float z_ = z * r.w + w * r.z + x * r.y - y * r.x;
	
	return quat(x_, y_, z_, w_);
}

quat quat::operator*(const vec3 &r) const
{
	const float w_ = -x * r.x - y * r.y - z * r.z;
	const float x_ =  w * r.x + y * r.z - z * r.y;
	const float y_ =  w * r.y + z * r.x - x * r.z;
	const float z_ =  w * r.z + x * r.y - y * r.x;
	
	return quat(x_, y_, z_, w_);
}

quat quat::operator*(float r) const
{
	quat result;
	result.x = x * r;
	result.y = y * r;
	result.z = z * r;
	result.w = w * r;
	return result;
}

quat &quat::operator*=(const quat &r)
{
	*this = operator*(r);
	return *this;
}

quat &quat::operator*=(const vec3 &r)
{
	*this = operator*(r);
	return *this;
}

quat &quat::operator*=(float r)
{
	*this = operator*(r);
	return *this;
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