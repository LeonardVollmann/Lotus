#include "transform.hpp"
#include "../maths/vector.hpp"
#include "../maths/quaternion.hpp"
#include "../maths/matrix.hpp"

namespace lotus {

	const Transform *Transform::CURRENT;

	Transform::Transform(const maths::vec3f &pos, const maths::fquat &rot,
						 const maths::vec3f &scale) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_parent(nullptr) {}

	void Transform::bind() const
	{
		CURRENT = this;
	}

	maths::mat4f Transform::getTransformation() const
	{
		maths::mat4f transformation = maths::translation<float, 4>(m_pos) *
										maths::rotation<float, 4>(m_rot) *
										maths::scale<float, 4>(m_scale);

		transformation = m_parent ? m_parent->getTransformation() * transformation : transformation;
		return transformation;
	}

	void Transform::translate(const maths::vec3f &translation)
	{
		m_pos += translation;
	}

	void Transform::rotate(const maths::fquat &rotation)
	{
		m_rot = maths::normalize(rotation * m_rot);
	}

	void Transform::rotate(const maths::vec3f &axis, float angle)
	{
		rotate(maths::axisAngle(axis, angle));
	}

	void Transform::scale(const maths::vec3f &scale)
	{
		m_scale *= scale;
	}

	void Transform::setPos(const maths::vec3f &pos)
	{
		m_pos = pos;
	}

	void Transform::setRot(const maths::fquat &rot)
	{
		m_rot = rot;
	}

	void Transform::setScale(const maths::vec3f &scale)
	{
		m_scale = scale;
	}

}
