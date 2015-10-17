#include "transform.hpp"

namespace lotus {

	const Transform *Transform::CURRENT;

	Transform::Transform(const maths::Vector3f &pos, const maths::QuaternionF &rot,
						 const maths::Vector3f &scale) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_parent(nullptr) {}

	void Transform::bind() const
	{
		CURRENT = this;
	}

	maths::Matrix4f Transform::getTransformation() const
	{
		maths::Matrix4f transformation = maths::translation<float>(m_pos) *
										maths::rotation<float, 4>(m_rot) *
										maths::scale<float>(m_scale);

		transformation = m_parent ? m_parent->getTransformation() * transformation : transformation;
		return transformation;
	}

	void Transform::translate(const maths::Vector3f &translation)
	{
		m_pos += translation;
	}

	void Transform::rotate(const maths::QuaternionF &rotation)
	{
		m_rot = maths::normalize(m_rot * rotation);
	}

	void Transform::rotate(float angle, const maths::Vector3f &axis)
	{
		rotate(maths::QuaternionF(axis, angle));
	}

	void Transform::scale(const maths::Vector3f &scale)
	{
		m_scale *= scale;
	}

	void Transform::setPos(const maths::Vector3f &pos)
	{
		m_pos = pos;
	}

	void Transform::setRot(const maths::QuaternionF &rot)
	{
		m_rot = rot;
	}

	void Transform::setScale(const maths::Vector3f &scale)
	{
		m_scale = scale;
	}

}
