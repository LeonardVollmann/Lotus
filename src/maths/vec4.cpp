#include "vec4.hpp"

namespace lotus { namespace maths {

	vec4::vec4()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	vec4::vec4(const float &x, const float &y, const float &z, const float &w) :
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4 &vec4::add(const vec4 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	vec4 &vec4::subtract(const vec4 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		
		return *this;
	}

	vec4 &vec4::multiply(const vec4 &other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		
		return *this;
	}

	vec4 &vec4::divide(const vec4 &other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		
		return *this;
	}

	vec4 operator+(const vec4 &left, const vec4 &right)
	{
		vec4 result;

		result.x = left.x + right.x;
		result.y = left.y + right.y;
		result.z = left.z + right.z;
		result.w = left.w + right.w;

		return result;
	}

	vec4 operator-(const vec4 &left, const vec4 &right)
	{
		vec4 result;

		result.x = left.x - right.x;
		result.y = left.y - right.y;
		result.z = left.z - right.z;
		result.w = left.w - right.w;
		
		return result;
	}

	vec4 operator*(const vec4 &left, const vec4 &right)
	{
		vec4 result;

		result.x = left.x * right.x;
		result.y = left.y * right.y;
		result.z = left.z * right.z;
		result.w = left.w * right.w;
		
		return result;
	}

	vec4 operator/(const vec4 &left, const vec4 &right)
	{
		vec4 result;

		result.x = left.x / right.x;
		result.y = left.y / right.y;
		result.z = left.z / right.z;
		result.w = left.w / right.w;
		
		return result;
	}

	bool operator==(const vec4 &other)
	{
		reuturn x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool operator!=(const vec4 &other)
	{
		return !(*this == other);
	}

	vec4 &operator+=(const vec4 &other)
	{
		return add(other);
	}	

	vec4 &operator-=(const vec4 &other)
	{
		return subtract(other);
	}	

	vec4 &operator*=(const vec4 &other)
	{
		return multiply(other);
	}	

	vec4 &operator/=(const vec4 &other)
	{
		return divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vector)
	{
		stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}

} }