#include "lotus_transform.hpp"

namespace lotus {

	Transform::Transform(const maths::vec3 &pos, const maths::quat &rot, const maths::vec3 &scale) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}

	maths::mat4 Transform::getTransformation() const
	{
		return maths::mat4::translation(m_pos) * 
			maths::mat4::rotation(m_rot) * 
			maths::mat4::scale(m_scale);
	}

	void Transform::translate(const maths::vec3 &translation)
	{
		m_pos += translation;
	}

	void Transform::rotate(const maths::quat &rotation)
	{
		m_rot *= rotation;
	}

	void Transform::rotate(float angle, const maths::vec3 &axis)
	{
		m_rot *= maths::quat(angle, axis);
	}

	void Transform::scale(const maths::vec3 &scale)
	{
		m_scale += scale;
	}

	void Transform::setPos(const maths::vec3 &pos)
	{
		m_pos = pos;
	}

	void Transform::setRot(const maths::quat &rot)
	{
		m_rot = rot;
	}

	void Transform::setScale(const maths::vec3 &scale)
	{
		m_scale = scale;
	}

}