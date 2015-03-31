#ifndef LOTUS_QUAT_HPP_INCLUDED
#define LOTUS_QUAT_HPP_INCLUDED

namespace lotus { namespace maths { 

	struct vec3;

	struct quat
	{
		float x, y, z, w;

		quat(float x, float y, float z, float w);

		float lengthSqr() const;
		float length() const;
		quat &normalize();

		quat conjugate() const;

		friend quat operator*(const quat &left, const quat &right);
		friend quat operator*(const quat &left, const vec3 &right);

		quat &multiply(const quat &other);
		quat &operator*=(const quat &other);
	};

} }

#endif