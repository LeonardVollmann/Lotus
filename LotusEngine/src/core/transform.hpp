#ifndef LOTUS_TRANSFORM_HPP_INCLUDED
#define LOTUS_TRANSFORM_HPP_INCLUDED

#include "../core/maths.hpp"

namespace lotus {

	class Transform
	{
	public:
		static const Transform *CURRENT;
	private:
		maths::Vector3f m_pos;
		maths::QuaternionF m_rot;
		maths::Vector3f m_scale;
		Transform 	*m_parent;
	public:
		Transform(const maths::Vector3f &pos = maths::Vector3f(0.0f, 0.0f, 0.0f),
			const maths::QuaternionF &rot = maths::QuaternionF(0.0f, 0.0f, 0.0f, 1.0f),
			const maths::Vector3f &scale = maths::Vector3f(1.0f, 1.0f, 1.0f));

		void bind() const;

		maths::Matrix4f getTransformation() const;

		void translate(const maths::Vector3f &translation);
		void rotate(const maths::QuaternionF &rotation);
		void rotate(float angle, const maths::Vector3f &axis);
		void scale(const maths::Vector3f &scale);

		void setPos(const maths::Vector3f &pos);
		void setRot(const maths::QuaternionF &rot);
		void setScale(const maths::Vector3f &scale);

		inline const maths::Vector3f &getPos()		const { return m_pos; }
		inline const maths::QuaternionF &getRot()	const { return m_rot; }
		inline const maths::Vector3f &getScale()	const { return m_scale; }
		inline Transform *getParent()				const { return m_parent; }

		inline maths::Vector3f &getPos() 	{ return m_pos; }
		inline maths::QuaternionF &getRot() { return m_rot; }
		inline maths::Vector3f &getScale() 	{ return m_scale; }

		inline void setParent(Transform *parent) { m_parent = parent; }
	};

}

#endif