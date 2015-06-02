#ifndef LOTUS_TRANSFORM_HPP_INCLUDED
#define LOTUS_TRANSFORM_HPP_INCLUDED

#include "lotus_vec3.hpp"
#include "lotus_mat4.hpp"
#include "lotus_quat.hpp"

class Transform
{
private:
	vec3 m_pos;
	quat m_rot;
	vec3 m_scale;
public:
	Transform(const vec3 &pos = vec3(0.0f, 0.0f, 0.0f),
		const quat &rot = quat(0.0f, 0.0f, 0.0f, 1.0f),
		const vec3 &scale = vec3(1.0f, 1.0f, 1.0f));

	mat4 getTransformation() const;

	void translate(const vec3 &translation);
	void rotate(const quat &rotation);
	void rotate(float angle, const vec3 &axis);
	void scale(const vec3 &scale);

	void setPos(const vec3 &pos);
	void setRot(const quat &rot);
	void setScale(const vec3 &scale);

	inline const vec3 &getPos() 	const { return m_pos; }
	inline const quat &getRot() 	const { return m_rot; }
	inline const vec3 &getScale() 	const { return m_scale; }
};

#endif