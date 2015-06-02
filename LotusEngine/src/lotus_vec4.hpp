#ifndef LOTUS_VEC4_HPP_INCLUDED
#define LOTUS_VEC4_HPP_INCLUDED

#include <iostream>

class vec4
{
public:
	static const vec4 ZERO;
	
	float x, y, z, w;

	vec4();
	vec4(float value);
	vec4(float x, float y, float z, float w);

	vec4 operator+(const vec4 &r) const;
	vec4 operator-(const vec4 &r) const;
	vec4 operator*(const vec4 &r) const;
	vec4 operator/(const vec4 &r) const;
	
	vec4 operator+(float r) const;
	vec4 operator-(float r) const;
	vec4 operator*(float r) const;
	vec4 operator/(float r) const;
	
	vec4 &operator+=(const vec4 &r);
	vec4 &operator-=(const vec4 &r);
	vec4 &operator*=(const vec4 &r);
	vec4 &operator/=(const vec4 &r);
	
	vec4 &operator+=(float r);
	vec4 &operator-=(float r);
	vec4 &operator*=(float r);
	vec4 &operator/=(float r);

	bool operator==(const vec4 &r) const;
	bool operator!=(const vec4 &r) const;
	bool operator==(float r) const;
	bool operator!=(float r) const;
	
	float dot(const vec4 &other) const;
	float lengthSqr() const;
	float length() const;
	vec4 &normalize();

	friend std::ostream &operator<<(std::ostream &stream, const vec4 &vector);
};

#endif