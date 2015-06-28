#include "lotus_freemove.hpp"
#include "lotus_input.hpp"

FreeMove::FreeMove(float speed) :
	m_speed(speed) {}

void FreeMove::update(float delta)
{
	if (Input::getKey(GLFW_KEY_W))
	{
		move(getTransform().getRot().getBack(), m_speed * delta);
	}
	if (Input::getKey(GLFW_KEY_A))
	{
		move(getTransform().getRot().getLeft(), m_speed * delta);
	}
	if (Input::getKey(GLFW_KEY_S))
	{
		move(getTransform().getRot().getForward(), m_speed * delta);
	}
	if (Input::getKey(GLFW_KEY_D))
	{
		move(getTransform().getRot().getRight(), m_speed * delta);
	}
}

void FreeMove::move(const vec3 &axis, float amount)
{
	getTransform().translate(axis * vec3(amount));
}