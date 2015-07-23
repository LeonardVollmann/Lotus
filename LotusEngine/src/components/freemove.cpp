#include "freemove.hpp"
#include "../core/entity.hpp"
#include "../core/input.hpp"

namespace lotus {

FreeMove::FreeMove(float speed) :
	m_speed(speed) {}

	void FreeMove::update(float delta)
	{
		if (Input::getKey(GLFW_KEY_W))
		{
			move(m_entity->getTransform().getRot().getBack(), m_speed * delta);
		}
		if (Input::getKey(GLFW_KEY_A))
		{
			move(m_entity->getTransform().getRot().getLeft(), m_speed * delta);
		}
		if (Input::getKey(GLFW_KEY_S))
		{
			move(m_entity->getTransform().getRot().getForward(), m_speed * delta);
		}
		if (Input::getKey(GLFW_KEY_D))
		{
			move(m_entity->getTransform().getRot().getRight(), m_speed * delta);
		}
	}

	void FreeMove::move(const maths::vec3 &axis, float amount)
	{
		m_entity->getTransform().translate(axis * maths::vec3(amount));
	}

}