#include "vec3.hpp"

namespace lotus { namespace maths {

	vec3::vec3()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	vec3::vec3(const float &x, const float &y, const float &z) :
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3 &vec3::add(const vec3 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	vec3 &vec3::subtract(const vec3 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		
		return *this;
	}

	vec3 &vec3::multiply(const vec3 &other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		
		return *this;
	}

	vec3 &vec3::divide(const vec3 &other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		
		return *this;
	}

	vec3 operator+(const vec3 &left, const vec3 &right)
	{
		vec3 result;

		result.x = left.x + right.x;
		result.y = left.y + right.y;
		result.z = left.z + right.z;

		return result;
	}

	vec3 operator-(const vec3 &left, const vec3 &right)
	{
		vec3 result;

		result.x = left.x - right.x;
		result.y = left.y - right.y;
		result.z = left.z - right.z;
		
		return result;
	}

	vec3 operator*(const vec3 &left, const vec3 &right)
	{
		vec3 result;

		result.x = left.x * right.x;
		result.y = left.y * right.y;
		result.z = left.z * right.z;
		
		return result;
	}

	vec3 operator/(const vec3 &left, const vec3 &right)
	{
		vec3 result;

		result.x = left.x / right.x;
		result.y = left.y / right.y;
		result.z = left.z / right.z;
		
		return result;
	}

	bool operator==(const vec3 &other)
	{
		reuturn x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const vec3 &other)
	{
		return !(*this == other);
	}

	vec3 &operator+=(const vec3 &other)
	{
		return add(other);
	}	

	vec3 &operator-=(const vec3 &other)
	{
		return subtract(other);
	}	

	vec3 &operator*=(const vec3 &other)
	{
		return multiply(other);
	}	

	vec3 &operator/=(const vec3 &other)
	{
		return divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector)
	{
		stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

} }