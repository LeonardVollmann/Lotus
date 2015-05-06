#ifndef LOTUS_VEC3_HPP_INCLUDED
#define LOTUS_VEC3_HPP_INCLUDED

#include <iostream>

class quat;

class vec3
{
public:
	static const vec3 ZERO;
	
	float x, y, z;

	vec3();
	vec3(float value);
	vec3(float x, float y, float z);

	vec3 operator+(const vec3 &r) const;
	vec3 operator-(const vec3 &r) const;
	vec3 operator*(const vec3 &r) const;
	vec3 operator/(const vec3 &r) const;
	
	vec3 operator+(float r) const;
	vec3 operator-(float r) const;
	vec3 operator*(float r) const;
	vec3 operator/(float r) const;
	
	vec3 &operator+=(const vec3 &r);
	vec3 &operator-=(const vec3 &r);
	vec3 &operator*=(const vec3 &r);
	vec3 &operator/=(const vec3 &r);
	
	vec3 &operator+=(float r);
	vec3 &operator-=(float r);
	vec3 &operator*=(float r);
	vec3 &operator/=(float r);
	
	bool operator==(const vec3 &r) const;
	bool operator!=(const vec3 &r) const;
	bool operator==(float r) const;
	bool operator!=(float r) const;
	
	float dot(const vec3 &other) const;
	vec3 cross(const vec3 &other) const;
	float lengthSqr() const;
	float length() const;
	vec3 &normalize();
	vec3 &rotate(const quat &rotation);
	vec3 &rotate(float angle, const vec3 &axis);

	friend std::ostream &operator<<(std::ostream &stream, const vec3 &vector);
};

#endif