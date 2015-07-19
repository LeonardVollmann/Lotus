#include "vec2.hpp"

#include <cmath>

namespace lotus { namespace maths {

	const vec2 vec2::ZERO = vec2();

	vec2::vec2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	vec2::vec2(float value)
	{
		this->x = value;
		this->y = value;
	}

	vec2::vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	vec2 vec2::operator+(const vec2 &r) const
	{
		vec2 result;
		result.x = x + r.x;
		result.y = y + r.y;
		return result;
	}

	vec2 vec2::operator-(const vec2 &r) const
	{
		vec2 result;
		result.x = x - r.x;
		result.y = y - r.y;
		return result;
	}

	vec2 vec2::operator*(const vec2 &r) const
	{
		vec2 result;
		result.x = x * r.x;
		result.y = y * r.y;
		return result;
	}

	vec2 vec2::operator/(const vec2 &r) const
	{
		vec2 result;
		result.x = x / r.x;
		result.y = y / r.y;
		return result;
	}

	vec2 vec2::operator+(float r) const
	{
		vec2 result;
		result.x = x + r;
		result.y = y + r;
		return result;
	}

	vec2 vec2::operator-(float r) const
	{
		vec2 result;
		result.x = x - r;
		result.y = y - r;
		return result;
	}

	vec2 vec2::operator*(float r) const
	{
		vec2 result;
		result.x = x * r;
		result.y = y * r;
		return result;
	}

	vec2 vec2::operator/(float r) const
	{
		vec2 result;
		result.x = x / r;
		result.y = y / r;
		return result;
	}

	vec2 &vec2::operator+=(const vec2 &r)
	{
		*this = operator+(r);
		return *this;
	}

	vec2 &vec2::operator-=(const vec2 &r)
	{
		*this = operator-(r);
		return *this;
	}

	vec2 &vec2::operator*=(const vec2 &r)
	{
		*this = operator*(r);
		return *this;
	}

	vec2 &vec2::operator/=(const vec2 &r)
	{
		*this = operator/(r);
		return *this;
	}

	vec2 &vec2::operator+=(float r)
	{
		*this = operator+(r);
		return *this;
	}

	vec2 &vec2::operator-=(float r)
	{
		*this = operator-(r);
		return *this;
	}

	vec2 &vec2::operator*=(float r)
	{
		*this = operator*(r);
		return *this;
	}

	vec2 &vec2::operator/=(float r)
	{
		*this = operator/(r);
		return *this;
	}

	bool vec2::operator==(const vec2 &r) const
	{
		return x == r.x && y == r.y;
	}

	bool vec2::operator!=(const vec2 &r) const
	{
		return !operator==(r);
	}

	bool vec2::operator==(float r) const
	{
		return x == r && y == r;
	}

	bool vec2::operator!=(float r) const
	{
		return !operator==(r);
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

	std::ostream& operator<<(std::ostream& stream, const vec2& vector)
	{
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

} }