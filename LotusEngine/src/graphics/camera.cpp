#include "camera.hpp"
#include "../core/input.hpp"
#include "../maths/vec3.hpp"

namespace lotus { namespace graphics {

	const Camera *Camera::CURRENT;

	Camera::Camera(const maths::mat4 &projection) :
		m_projection(projection)
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