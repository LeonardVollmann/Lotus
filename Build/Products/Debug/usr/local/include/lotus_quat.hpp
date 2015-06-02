#ifndef LOTUS_QUAT_HPP_INCLUDED
#define LOTUS_QUAT_HPP_INCLUDED

class vec3;

class quat
{
public:
	float x, y, z, w;

	quat();
	quat(float x, float y, float z, float w);
	quat(float angle, const vec3 &axis);

	quat operator*(const quat &r) const;
	quat operator*(const vec3 &r) const;
	quat operator*(float r) const;

	quat &operator*=(const quat &r);
	quat &operator*=(const vec3 &r);
	quat &operator*=(float r);
	
	bool operator==(const quat &r);
	bool operator!=(const quat &r);

	float lengthSqr() const;
	float length() const;
	quat &normalize();
	quat conjugate() const;
	
	vec3 getForward() const;
	vec3 getBack() const;
	vec3 getUp() const;
	vec3 getDown() const;
	vec3 getRight() const;
	vec3 getLeft() const;
};

#endif