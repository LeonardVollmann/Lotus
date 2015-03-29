#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

namespace lotus { namespace maths {

	struct vec3
	{
		float x, y, z;

		vec3();
		vec3(const float &x, const float &y, const float &z);

		vec3 &add(const vec3 &other);
		vec3 &subtract(const vec3 &other);
		vec3 &multiply(const vec3 &other);
		vec3 &divide(const vec3 &other);

		float dot(const vec3 &other) const;
		float lengthSqr() const;
		float length() const;
		vec3 &normalize();

		friend vec3 operator+(const vec3 &left, const vec3 &right);
		friend vec3 operator-(const vec3 &left, const vec3 &right);
		friend vec3 operator*(const vec3 &left, const vec3 &right);
		friend vec3 operator/(const vec3 &left, const vec3 &right);
		friend vec3 cross(const vec3 &a, const vec3 &b);

		friend bool operator==(const vec3 &left, const vec3 &right);
		friend bool operator!=(const vec3 &left, const vec3 &right);

		vec3 &operator+=(const vec3 &other);
		vec3 &operator-=(const vec3 &other);
		vec3 &operator*=(const vec3 &other);
		vec3 &operator/=(const vec3 &other);

		friend std::ostream &operator<<(std::ostream &stream, const vec3 &vector);
	};

} }

#endif