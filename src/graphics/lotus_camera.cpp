#include "lotus_camera.hpp"
#include "../core/lotus_input.hpp"
#include "../maths/lotus_vec3.hpp"

void Camera::update()
{
	const float speed = 0.25f;
	const float rotSpeed = 0.05f;
	const float sensitivity = 0.5f;

	if (Input::getKey(GLFW_KEY_W)) move(m_transform.getRot().getForward(), -speed);
	if (Input::getKey(GLFW_KEY_S)) move(m_transform.getRot().getForward(), speed);
	if (Input::getKey(GLFW_KEY_D)) move(m_transform.getRot().getRight(), speed);
	if (Input::getKey(GLFW_KEY_A)) move(m_transform.getRot().getRight(), -speed);

	if (!Input::isMouseLocked())
	{
		if (Input::getKey(GLFW_KEY_UP)) m_transform.rotate(quat(rotSpeed, m_transform.getRot().getRight()));
		if (Input::getKey(GLFW_KEY_DOWN)) m_transform.rotate(quat(rotSpeed, m_transform.getRot().getLeft()));
		if (Input::getKey(GLFW_KEY_RIGHT)) m_transform.rotate(quat(-rotSpeed, vec3(0.0f, 1.0f, 0.0f)));
		if (Input::getKey(GLFW_KEY_LEFT)) m_transform.rotate(quat(rotSpeed, vec3(0.0f, 1.0f, 0.0f)));
	}
	else
	{
		if (Input::getCursorPosDelta().y != 0)
		{
			m_transform.rotate(quat(Input::getCursorPosDelta().y * sensitivity, m_transform.getRot().getRight()));
		}
		if (Input::getCursorPosDelta().x != 0)
		{
			m_transform.rotate(quat(Input::getCursorPosDelta().x * sensitivity, vec3(0.0f, 1.0f, 0.0f)));
		}
	}
}

mat4 Camera::getViewMatrix() const
{
	return mat4(m_transform.getRot().conjugate().normalize()) * mat4::translation(m_transform.getPos() * vec3(-1.0f));
}

void Camera::move(const vec3 &axis, float amount)
{
	m_transform.translate(axis * vec3(amount));
}