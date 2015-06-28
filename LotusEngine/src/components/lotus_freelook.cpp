#include "lotus_freelook.hpp"
#include "lotus_input.hpp"

FreeLook::FreeLook(float turnSpeed) :
	m_turnSpeed(turnSpeed) {}

void FreeLook::update(float delta)
{
	if (Input::isMouseLocked())
	{
		if (Input::getCursorPosDelta() != vec2(0.0f)) std::cout << Input::getCursorPosDelta() << std::endl;
	}
	else
	{
		if (Input::getKey(GLFW_KEY_UP))
		{
			getTransform().rotate(m_turnSpeed * delta, getTransform().getRot().getRight());
		}
		if (Input::getKey(GLFW_KEY_DOWN))
		{
			getTransform().rotate(-m_turnSpeed * delta, getTransform().getRot().getRight());
		}
		if (Input::getKey(GLFW_KEY_LEFT))
		{
			getTransform().rotate(m_turnSpeed * delta, vec3(0.0f, 1.0f, 0.0f));
		}
		if (Input::getKey(GLFW_KEY_RIGHT))
		{
			getTransform().rotate(-m_turnSpeed * delta, vec3(0.0f, 1.0f, 0.0f));
		}
	}
}