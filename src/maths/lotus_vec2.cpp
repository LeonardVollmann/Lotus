#include "lotus_vec2.hpp"

#include <cmath>

namespace lotus { namespace maths {

	vec2::vec2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	vec2::vec2(const float &value)
	{
		this->x = value;
		this->y = value;
	}

	vec2::vec2(const float &x, const float &y)
	{
		this->x = x;
		this->y = y;
	}

	vec2 &vec2::add(const vec2 &other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	vec2 &vec2::subtract(const vec2 &other)
	{
		x -= other.x;
		y -= other.y;
		
		return *this;
	}

	vec2 &vec2::multiply(const vec2 &other)
	{
		x *= other.x;
		y *= other.y;
		
		return *this;
	}

	vec2 &vec2::divide(const vec2 &other)
	{
		x /= other.x;
		y /= other.y;
		
		return *this;
	}

	float vec2::dot(const vec2 &other) const
	{
		return x * other.x + y * other.y;
	}

	float vec2::lengthSqr() const
	{
		return dot(*this);
	}

	float vec2::length() const
	{
		return sqrtf(lengthSqr());
	}

	vec2 &vec2::normalize()
	{
		float length = this->length();
		x /= length;
		y /= length;

		return *this;
	}

	vec2 operator+(const vec2 &left, const vec2 &right)
	{
		vec2 result;

		result.x = left.x + right.x;
		result.y = left.y + right.y;

		return result;
	}

	vec2 operator-(const vec2 &left, const vec2 &right)
	{
		vec2 result;

		result.x = left.x - right.x;
		result.y = left.y - right.y;
		
		return result;
	}

	vec2 operator*(const vec2 &left, const vec2 &right)
	{
		vec2 result;

		result.x = left.x * right.x;
		result.y = left.y * right.y;
		
		return result;
	}

	vec2 operator/(const vec2 &left, const vec2 &right)
	{
		vec2 result;

		result.x = left.x / right.x;
		result.y = left.y / right.y;
		
		return result;
	}

	bool operator==(const vec2 &left, const vec2 &right)
	{
		return left.x == right.x && left.y == right.y;
	}

	bool operator!=(const vec2 &left, const vec2 &right)
	{
		return !(left == right);
	}

	vec2 &vec2::operator+=(const vec2 &other)
	{
		return add(other);
	}	

	vec2 &vec2::operator-=(const vec2 &other)
	{
		return subtract(other);
	}	

	vec2 &vec2::operator*=(const vec2 &other)
	{
		return multiply(other);
	}	

	vec2 &vec2::operator/=(const vec2 &other)
	{
		return divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& vector)
	{
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

} }