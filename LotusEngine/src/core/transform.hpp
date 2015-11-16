#ifndef LOTUS_TRANSFORM_HPP_INCLUDED
#define LOTUS_TRANSFORM_HPP_INCLUDED

#include "../maths/types.hpp"

namespace lotus {

	class Transform
	{
	public:
		static const Transform *CURRENT;

		Transform(const maths::vec3f &pos = maths::vec3f(0.0f, 0.0f, 0.0f),
			const maths::fquat &rot = maths::fquat(0.0f, 0.0f, 0.0f, 1.0f),
			const maths::vec3f &scale = maths::vec3f(1.0f, 1.0f, 1.0f));

		void bind() const;

		maths::mat4f getTransformation() const;

		void translate(const maths::vec3f &translation);
		void rotate(const maths::fquat &rotation);
		void rotate(const maths::vec3f &axis, float angle);
		void scale(const maths::vec3f &scale);

		void setPos(const maths::vec3f &pos);
		void setRot(const maths::fquat &rot);
		void setScale(const maths::vec3f &scale);

		inline const maths::vec3f &getPos()		const { return m_pos; }
		inline const maths::fquat &getRot()	const { return m_rot; }
		inline const maths::vec3f &getScale()	const { return m_scale; }
		inline Transform *getParent()				const { return m_parent; }

		inline maths::vec3f &getPos() 	{ return m_pos; }
		inline maths::fquat &getRot() { return m_rot; }
		inline maths::vec3f &getScale() 	{ return m_scale; }

		inline void setParent(Transform *parent) { m_parent = parent; }
	protected:
	private:
		maths::vec3f		m_pos;
		maths::fquat	m_rot;
		maths::vec3f		m_scale;
		Transform			*m_parent;
	};

}

#endif