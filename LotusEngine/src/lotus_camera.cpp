#include "lotus_camera.hpp"
#include "lotus_input.hpp"
#include "lotus_vec3.hpp"

const Camera *Camera::CURRENT;

Camera::Camera()
{
	bind();
}

mat4 Camera::getViewMatrix() const
{
	return mat4(m_transform.getRot().conjugate().normalize()) * mat4::translation(m_transform.getPos() * vec3(-1.0f));
}

void Camera::bind() const
{
	CURRENT = this;
}