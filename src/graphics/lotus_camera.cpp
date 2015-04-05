#include "lotus_camera.hpp"
#include "../core/lotus_input.hpp"
#include "../maths/lotus_vec3.hpp"

namespace lotus { namespace graphics {

	void Camera::update()
	{
		const float speed = 0.25f;
		const float rotSpeed = 0.1f;
		maths::vec3 translation;
		maths::quat rotation;

		if (Input::getKey(GLFW_KEY_W)) translation += m_transform.getRot().getBack() * maths::vec3(speed);
		if (Input::getKey(GLFW_KEY_S)) translation += m_transform.getRot().getForward() * maths::vec3(speed);
		if (Input::getKey(GLFW_KEY_D)) translation += m_transform.getRot().getRight() * maths::vec3(speed);
		if (Input::getKey(GLFW_KEY_A)) translation += m_transform.getRot().getLeft() * maths::vec3(speed);

		if (!Input::isMouseLocked())
		{
			if (Input::getKey(GLFW_KEY_UP)) rotation *= maths::quat(rotSpeed, maths::vec3(1.0f, 0.0f, 0.0f));
			if (Input::getKey(GLFW_KEY_DOWN)) rotation *= maths::quat(rotSpeed, maths::vec3(-1.0f, 0.0f, 0.0f));
			if (Input::getKey(GLFW_KEY_RIGHT)) rotation *= maths::quat(rotSpeed, maths::vec3(0.0f, -1.0f, 0.0f));
			if (Input::getKey(GLFW_KEY_LEFT)) rotation *= maths::quat(rotSpeed, maths::vec3(0.0f, 1.0f, 0.0f));
		}

		m_transform.translate(translation);
		m_transform.rotate(rotation);
	}

	maths::mat4 Camera::getViewMatrix() const
	{
		return maths::mat4(m_transform.getRot().conjugate().normalize()) * maths::mat4::translation(m_transform.getPos() * maths::vec3(-1.0f));
	}

} }