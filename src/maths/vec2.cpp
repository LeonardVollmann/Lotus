#include "vec2.hpp"

namespace lotus { namespace maths {

	vec2::vec2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	vec2::vec2(const float &x, const float &y) :
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

	bool operator==(const vec2 &other)
	{
		reuturn x == other.x && y == other.y;
	}

	bool operator!=(const vec2 &other)
	{
		return !(*this == other);
	}

	vec2 &operator+=(const vec2 &other)
	{
		return add(other);
	}	

	vec2 &operator-=(const vec2 &other)
	{
		return subtract(other);
	}	

	vec2 &operator*=(const vec2 &other)
	{
		return multiply(other);
	}	

	vec2 &operator/=(const vec2 &other)
	{
		return divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& vector)
	{
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

} }