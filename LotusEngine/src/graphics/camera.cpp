#include "camera.hpp"
#include "input.hpp"
#include "vec3.hpp"

namespace lotus { namespace graphics {

	const Camera *Camera::CURRENT;

	Camera::Camera()
	{
		bind();
	}

	maths::mat4 Camera::getViewMatrix() const
	{
		return maths::mat4(m_transform.getRot().conjugate().normalize()) * maths::mat4::translation(m_transform.getPos() * maths::vec3(-1.0f));
	}

	void Camera::bind() const
	{
		CURRENT = this;
	}

} }