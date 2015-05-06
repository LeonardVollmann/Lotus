#include "lotus_vec3.hpp"
#include "lotus_quat.hpp"

#include <cmath>

const vec3 vec3::ZERO = vec3();

vec3::vec3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

vec3::vec3(float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3 vec3::operator+(const vec3 &r) const
{
	vec3 result;
	result.x = x + r.x;
	result.y = y + r.y;
	result.z = z + r.z;
	return result;
}

vec3 vec3::operator-(const vec3 &r) const
{
	vec3 result;
	result.x = x - r.x;
	result.y = y - r.y;
	result.z = z - r.z;
	return result;
}

vec3 vec3::operator*(const vec3 &r) const
{
	vec3 result;
	result.x = x * r.x;
	result.y = y * r.y;
	result.z = z * r.z;
	return result;
}

vec3 vec3::operator/(const vec3 &r) const
{
	vec3 result;
	result.x = x / r.x;
	result.y = y / r.y;
	result.z = z / r.z;
	return result;
}

vec3 vec3::operator+(float r) const
{
	vec3 result;
	result.x = x + r;
	result.y = y + r;
	result.z = z + r;
	return result;
}

vec3 vec3::operator-(float r) const
{
	vec3 result;
	result.x = x - r;
	result.y = y - r;
	result.z = z - r;
	return result;
}

vec3 vec3::operator*(float r) const
{
	vec3 result;
	result.x = x * r;
	result.y = y * r;
	result.z = z * r;
	return result;
}

vec3 vec3::operator/(float r) const
{
	vec3 result;
	result.x = x / r;
	result.y = y / r;
	result.z = z / r;
	return result;
}

vec3 &vec3::operator+=(const vec3 &r)
{
	*this = operator+(r);
	return *this;
}

vec3 &vec3::operator-=(const vec3 &r)
{
	*this = operator-(r);
	return *this;
}

vec3 &vec3::operator*=(const vec3 &r)
{
	*this = operator*(r);
	return *this;
}

vec3 &vec3::operator/=(const vec3 &r)
{
	*this = operator/(r);
	return *this;
}

vec3 &vec3::operator+=(float r)
{
	*this = operator+(r);
	return *this;
}

vec3 &vec3::operator-=(float r)
{
	*this = operator-(r);
	return *this;
}

vec3 &vec3::operator*=(float r)
{
	*this = operator*(r);
	return *this;
}

vec3 &vec3::operator/=(float r)
{
	*this = operator/(r);
	return *this;
}

bool vec3::operator==(const vec3 &r) const
{
	return x == r.x && y == r.y && z == r.z;
}

bool vec3::operator!=(const vec3 &r) const
{
	return !operator==(r);
}

bool vec3::operator==(float r) const
{
	return x == r && y == r && z == r;
}

bool vec3::operator!=(float r) const
{
	return !operator==(r);
}

float vec3::dot(const vec3 &other) const
{
	return x * other.x + y * other.y + z * other.z;
}

vec3 vec3::cross(const vec3 &other) const
{
	vec3 result;
	
	result.x = y * other.z - z * other.y;
	result.y = z * other.x - x * other.z;
	result.z = x * other.y - y * other.x;
	
	return result;
}

float vec3::lengthSqr() const
{
	return dot(*this);
}

float vec3::length() const
{
	return sqrtf(lengthSqr());
}

vec3 &vec3::normalize()
{
	float length = this->length();
	x /= length;
	y /= length;
	z /= length;

	return *this;
}

vec3 &vec3::rotate(const quat &rotation)
{
	quat q = rotation * (*this) * rotation.conjugate();
	
	x = q.x;
	y = q.y;
	z = q.z;
	
	return *this;
}

vec3 &vec3::rotate(float angle, const vec3 &axis)
{
	return rotate(quat(angle, axis));
}

std::ostream& operator<<(std::ostream& stream, const vec3& vector)
{
	stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}