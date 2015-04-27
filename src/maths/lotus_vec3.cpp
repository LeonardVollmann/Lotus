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

vec3::vec3(const float &value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

vec3::vec3(const float &x, const float &y, const float &z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3 &vec3::add(const vec3 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

vec3 &vec3::subtract(const vec3 &other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	
	return *this;
}

vec3 &vec3::multiply(const vec3 &other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	
	return *this;
}

vec3 &vec3::divide(const vec3 &other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	
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

float vec3::dot(const vec3 &other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float vec3::lengthSqr() const
{
	return dot(*this);
}

float vec3::length() const
{
	return sqrtf(lengthSqr());
}

vec3 operator+(const vec3 &left, const vec3 &right)
{
	vec3 result;

	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;

	return result;
}

vec3 operator-(const vec3 &left, const vec3 &right)
{
	vec3 result;

	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
	
	return result;
}

vec3 operator*(const vec3 &left, const vec3 &right)
{
	vec3 result;

	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;
	
	return result;
}

vec3 operator/(const vec3 &left, const vec3 &right)
{
	vec3 result;

	result.x = left.x / right.x;
	result.y = left.y / right.y;
	result.z = left.z / right.z;
	
	return result;
}

vec3 &vec3::normalize()
{
	float length = this->length();
	x /= length;
	y /= length;
	z /= length;

	return *this;
}

vec3 cross(const vec3 &a, const vec3 &b)
{
	vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	return result;
}

bool operator==(const vec3 &left, const vec3 &right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}

bool operator!=(const vec3 &left, const vec3 &right)
{
	return !(left == right);
}

vec3 &vec3::operator+=(const vec3 &other)
{
	return add(other);
}	

vec3 &vec3::operator-=(const vec3 &other)
{
	return subtract(other);
}	

vec3 &vec3::operator*=(const vec3 &other)
{
	return multiply(other);
}	

vec3 &vec3::operator/=(const vec3 &other)
{
	return divide(other);
}

std::ostream& operator<<(std::ostream& stream, const vec3& vector)
{
	stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}