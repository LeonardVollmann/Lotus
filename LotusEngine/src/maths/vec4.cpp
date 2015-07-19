#include "vec4.hpp"

#include <cmath>

namespace lotus { namespace maths {

	const vec4 vec4::ZERO = vec4();

	vec4::vec4()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	vec4::vec4(float value)
	{
		this->x = value;
		this->y = value;
		this->z = value;
		this->w = value;
	}

	vec4::vec4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4 vec4::operator+(const vec4 &r) const
	{
		vec4 result;
		result.x = x + r.x;
		result.y = y + r.y;
		result.z = z + r.z;
		result.w = w + r.w;
		return result;
	}

	vec4 vec4::operator-(const vec4 &r) const
	{
		vec4 result;
		result.x = x - r.x;
		result.y = y - r.y;
		result.z = z - r.z;
		result.w = w - r.w;
		return result;
	}

	vec4 vec4::operator*(const vec4 &r) const
	{
		vec4 result;
		result.x = x * r.x;
		result.y = y * r.y;
		result.z = z * r.z;
		result.w = w * r.w;
		return result;
	}

	vec4 vec4::operator/(const vec4 &r) const
	{
		vec4 result;
		result.x = x / r.x;
		result.y = y / r.y;
		result.z = z / r.z;
		result.w = w / r.w;
		return result;
	}

	vec4 vec4::operator+(float r) const
	{
		vec4 result;
		result.x = x + r;
		result.y = y + r;
		result.z = z + r;
		result.w = w + r;
		return result;
	}

	vec4 vec4::operator-(float r) const
	{
		vec4 result;
		result.x = x - r;
		result.y = y - r;
		result.z = z - r;
		result.w = w - r;
		return result;
	}

	vec4 vec4::operator*(float r) const
	{
		vec4 result;
		result.x = x * r;
		result.y = y * r;
		result.z = z * r;
		result.w = w * r;
		return result;
	}

	vec4 vec4::operator/(float r) const
	{
		vec4 result;
		result.x = x / r;
		result.y = y / r;
		result.z = z / r;
		result.w = w / r;
		return result;
	}

	vec4 &vec4::operator+=(const vec4 &r)
	{
		*this = operator+(r);
		return *this;
	}

	vec4 &vec4::operator-=(const vec4 &r)
	{
		*this = operator-(r);
		return *this;
	}

	vec4 &vec4::operator*=(const vec4 &r)
	{
		*this = operator*(r);
		return *this;
	}

	vec4 &vec4::operator/=(const vec4 &r)
	{
		*this = operator/(r);
		return *this;
	}

	vec4 &vec4::operator+=(float r)
	{
		*this = operator+(r);
		return *this;
	}

	vec4 &vec4::operator-=(float r)
	{
		*this = operator-(r);
		return *this;
	}

	vec4 &vec4::operator*=(float r)
	{
		*this = operator*(r);
		return *this;
	}

	vec4 &vec4::operator/=(float r)
	{
		*this = operator/(r);
		return *this;
	}

	bool vec4::operator==(const vec4 &r) const
	{
		return x == r.x && y == r.y && z == r.z && w == r.w;
	}

	bool vec4::operator!=(const vec4 &r) const
	{
		return !operator==(r);
	}

	bool vec4::operator==(float r) const
	{
		return x == r && y == r && z == r && w == r;
	}

	bool vec4::operator!=(float r) const
	{
		return !operator==(r);
	}

	float vec4::dot(const vec4 &other) const
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	float vec4::lengthSqr() const
	{
		return dot(*this);
	}

	float vec4::length() const
	{
		return sqrtf(lengthSqr());
	}

	vec4 &vec4::normalize()
	{
		float length = this->length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vector)
	{
		stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}

} }