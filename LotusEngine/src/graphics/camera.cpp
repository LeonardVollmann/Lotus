#include "camera.hpp"
#include "../core/input.hpp"
#include "../core/maths.hpp"

namespace lotus { namespace graphics {

	const Camera *Camera::CURRENT;

	Camera::Camera()
	{
		bind();
	}

	maths::Matrix4f Camera::getViewMatrix() const
	{
		return maths::rotation<float, 4>(maths::normalized(maths::conjugate(m_transform.getRot()))) *
				maths::translation<float>(m_transform.getPos() * maths::Vector3f(-1.0f));
	}

	void Camera::bind() const
	{
		CURRENT = this;
	}

} }