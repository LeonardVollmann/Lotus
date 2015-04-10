#ifndef LOTUS_QUAT_HPP_INCLUDED
#define LOTUS_QUAT_HPP_INCLUDED

struct vec3;

struct quat
{
	float x, y, z, w;

	quat();
	quat(float x, float y, float z, float w);
	quat(float angle, const vec3 &axis);

	float lengthSqr() const;
	float length() const;
	quat &normalize();

	quat conjugate() const;

	friend quat operator*(const quat &left, const quat &right);
	friend quat operator*(const quat &left, const vec3 &right);

	quat &multiply(const quat &other);
	quat &operator*=(const quat &other);

	vec3 getForward() const;
	vec3 getBack() const;
	vec3 getUp() const;
	vec3 getDown() const;
	vec3 getRight() const;
	vec3 getLeft() const;
};

#endif