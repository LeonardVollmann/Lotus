#include "freelook.hpp"
#include "../core/entity.hpp"
#include "../core/input.hpp"

namespace lotus {

	FreeLook::FreeLook(float turnSpeed) :
		m_turnSpeed(turnSpeed) {}

	void FreeLook::update(float delta)
	{
		if (Input::isMouseLocked())
		{
//			if (Input::getCursorPosDelta() != maths::vec2(0.0f)) std::cout << Input::getCursorPosDelta() << std::endl;
		}
		else
		{
			if (Input::getKey(GLFW_KEY_UP))
			{
				m_entity->getTransform().rotate(m_turnSpeed * delta, maths::getRight(m_entity->getTransform().getRot()));
			}
			if (Input::getKey(GLFW_KEY_DOWN))
			{
				m_entity->getTransform().rotate(-m_turnSpeed * delta, maths::getRight(m_entity->getTransform().getRot()));
			}
			if (Input::getKey(GLFW_KEY_LEFT))
			{
				m_entity->getTransform().rotate(m_turnSpeed * delta, maths::Vector3f(0.0f, 1.0f, 0.0f));
			}
			if (Input::getKey(GLFW_KEY_RIGHT))
			{
				m_entity->getTransform().rotate(-m_turnSpeed * delta, maths::Vector3f(0.0f, 1.0f, 0.0f));
			}
		}
	}

}