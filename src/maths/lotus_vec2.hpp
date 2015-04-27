#ifndef LOTUS_VEC2_HPP_INCLUDED
#define LOTUS_VEC2_HPP_INCLUDED

#include <iostream>

struct vec2
{
	static const vec2 ZERO;
	
	float x, y;

	vec2();
	vec2(const float &value);
	vec2(const float &x, const float &y);

	vec2 &add(const vec2 &other);
	vec2 &subtract(const vec2 &other);
	vec2 &multiply(const vec2 &other);
	vec2 &divide(const vec2 &other);

	float dot(const vec2 &other) const;
	float lengthSqr() const;
	float length() const;
	vec2 &normalize();

	friend vec2 operator+(const vec2 &left, const vec2 &right);
	friend vec2 operator-(const vec2 &left, const vec2 &right);
	friend vec2 operator*(const vec2 &left, const vec2 &right);
	friend vec2 operator/(const vec2 &left, const vec2 &right);

	friend bool operator==(const vec2 &left, const vec2 &right);
	friend bool operator!=(const vec2 &left, const vec2 &right);

	vec2 &operator+=(const vec2 &other);
	vec2 &operator-=(const vec2 &other);
	vec2 &operator*=(const vec2 &other);
	vec2 &operator/=(const vec2 &other);

	friend std::ostream &operator<<(std::ostream &stream, const vec2 &vector);
};

#endif