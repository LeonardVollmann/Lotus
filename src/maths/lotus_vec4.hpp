#ifndef LOTUS_VEC4_HPP_INCLUDED
#define LOTUS_VEC4_HPP_INCLUDED

#include <iostream>

namespace lotus { namespace maths {

	struct vec4
	{
		float x, y, z, w;

		vec4();
		vec4(const float &value);
		vec4(const float &x, const float &y, const float &z, const float &w);

		vec4 &add(const vec4 &other);
		vec4 &subtract(const vec4 &other);
		vec4 &multiply(const vec4 &other);
		vec4 &divide(const vec4 &other);

		float dot(const vec4 &other) const;
		float lengthSqr() const;
		float length() const;
		vec4 &normalize();

		friend vec4 operator+(const vec4 &left, const vec4 &right);
		friend vec4 operator-(const vec4 &left, const vec4 &right);
		friend vec4 operator*(const vec4 &left, const vec4 &right);
		friend vec4 operator/(const vec4 &left, const vec4 &right);

		friend bool operator==(const vec4 &left, const vec4 &right);
		friend bool operator!=(const vec4 &left, const vec4 &right);

		vec4 &operator+=(const vec4 &other);
		vec4 &operator-=(const vec4 &other);
		vec4 &operator*=(const vec4 &other);
		vec4 &operator/=(const vec4 &other);

		friend std::ostream &operator<<(std::ostream &stream, const vec4 &vector);
	};

} }

#endif