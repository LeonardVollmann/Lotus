#include "lotus_transform.hpp"

namespace lotus {

	const Transform *Transform::CURRENT;

	Transform::Transform(const maths::vec3 &pos, const maths::quat &rot, const maths::vec3 &scale) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}

	void Transform::bind() const
	{
		CURRENT = this;
	}

	void Transform::unbind() const
	{
		CURRENT = nullptr;
	}

	maths::mat4 Transform::getTransformation() const
	{
		return maths::mat4::translation(m_pos) * 
			maths::mat4::rotation(m_rot) * 
			maths::mat4::scale(m_scale);
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