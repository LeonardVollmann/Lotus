#ifndef LOTUS_VEC2_HPP_INCLUDED
#define LOTUS_VEC2_HPP_INCLUDED

#include <iostream>

namespace lotus { namespace maths {

	class vec2
	{
	public:
		static const vec2 ZERO;
		
		float x, y;
		
		vec2();
		vec2(float value);
		vec2(float x, float y);

		vec2 operator+(const vec2 &r) const;
		vec2 operator-(const vec2 &r) const;
		vec2 operator*(const vec2 &r) const;
		vec2 operator/(const vec2 &r) const;
		
		vec2 operator+(float r) const;
		vec2 operator-(float r) const;
		vec2 operator*(float r) const;
		vec2 operator/(float r) const;
		
		vec2 &operator+=(const vec2 &r);
		vec2 &operator-=(const vec2 &r);
		vec2 &operator*=(const vec2 &r);
		vec2 &operator/=(const vec2 &r);
		
		vec2 &operator+=(float r);
		vec2 &operator-=(float r);
		vec2 &operator*=(float r);
		vec2 &operator/=(float r);
		
		bool operator==(const vec2 &r) const;
		bool operator!=(const vec2 &r) const;
		
		bool operator==(float r) const;
		bool operator!=(float r) const;
		
		float dot(const vec2 &other) const;
		float lengthSqr() const;
		float length() const;
		vec2 &normalize();

		friend std::ostream &operator<<(std::ostream &stream, const vec2 &vector);
	};

} }

#endif