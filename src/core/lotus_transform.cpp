#include "lotus_transform.hpp"

Transform::Transform(const vec3 &pos, const quat &rot, const vec3 &scale) :
	m_pos(pos),
	m_rot(rot),
	m_scale(scale) {}

mat4 Transform::getTransformation() const
{
	return mat4::translation(m_pos) * 
		mat4::rotation(m_rot) * 
		mat4::scale(m_scale);
}

void Transform::translate(const vec3 &translation)
{
	m_pos += translation;
}

void Transform::rotate(const quat &rotation)
{
	m_rot = (rotation * m_rot).normalize();
}

void Transform::rotate(float angle, const vec3 &axis)
{
	rotate(quat(angle, axis));
}

void Transform::scale(const vec3 &scale)
{
	m_scale *= scale;
}

void Transform::setPos(const vec3 &pos)
{
	m_pos = pos;
}

void Transform::setRot(const quat &rot)
{
	m_rot = rot;
}

void Transform::setScale(const vec3 &scale)
{
	m_scale = scale;
}