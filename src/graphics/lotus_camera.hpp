#ifndef LOTUS_CAMERA_HPP_INCLUDED
#define LOTUS_CAMERA_HPP_INCLUDED

#include "../core/lotus_transform.hpp"
#include "../maths/lotus_mat4.hpp"

namespace lotus { namespace graphics {

	class Camera
	{
	private:
		Transform m_transform;
	public:
		void update();
		maths::mat4 getViewMatrix() const;

		inline const Transform &getTransform() const { return m_transform; }
	private:
		void move(const maths::vec3 &axis, float amount);
	};

} }

#endif