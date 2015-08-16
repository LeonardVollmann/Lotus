#ifndef LOTUS_TRANSFORM_HPP_INCLUDED
#define LOTUS_TRANSFORM_HPP_INCLUDED

#include "../maths/vec3.hpp"
#include "../maths/mat4.hpp"
#include "../maths/quat.hpp"

namespace lotus {

	class Transform
	{
	public:
		static const Transform *CURRENT;
	private:
		maths::vec3 m_pos;
		maths::quat m_rot;
		maths::vec3 m_scale;
		Transform 	*m_parent;
	public:
		Transform(const maths::vec3 &pos = maths::vec3(0.0f, 0.0f, 0.0f),
			const maths::quat &rot = maths::quat(0.0f, 0.0f, 0.0f, 1.0f),
			const maths::vec3 &scale = maths::vec3(1.0f, 1.0f, 1.0f));

		void bind() const;

		maths::mat4 getTransformation() const;

		void translate(const maths::vec3 &translation);
		void rotate(const maths::quat &rotation);
		void rotate(float angle, const maths::vec3 &axis);
		void scale(const maths::vec3 &scale);

		void setPos(const maths::vec3 &pos);
		void setRot(const maths::quat &rot);
		void setScale(const maths::vec3 &scale);

		inline const maths::vec3 &getPos() 		const { return m_pos; }
		inline const maths::quat &getRot() 		const { return m_rot; }
		inline const maths::vec3 &getScale() 	const { return m_scale; }
		inline Transform *getParent()			const { return m_parent; }

		inline maths::vec3 &getPos() 	{ return m_pos; }
		inline maths::quat &getRot() 	{ return m_rot; }
		inline maths::vec3 &getScale() 	{ return m_scale; }

		inline void setParent(Transform *parent) { m_parent = parent; }
	};

}

#endif