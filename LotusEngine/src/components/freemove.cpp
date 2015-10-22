#include "freemove.hpp"
#include "../core/entity.hpp"
#include "../core/input.hpp"
#include "../core/maths.hpp"

namespace lotus {

FreeMove::FreeMove(float speed) :
	m_speed(speed) {}

	void FreeMove::update(float delta)
	{
		if (Input::getKey(GLFW_KEY_W))
		{
			move(maths::getForward(m_entity->getTransform().getRot()), m_speed * delta);
		}
		if (Input::getKey(GLFW_KEY_A))
		{
			move(maths::getLeft(m_entity->getTransform().getRot()), m_speed * delta);
		}
		if (Input::getKey(GLFW_KEY_S))
		{
			move(maths::getBack(m_entity->getTransform().getRot()), m_speed * delta);
		}
		if (Input::getKey(GLFW_KEY_D))
		{
			move(maths::getRight(m_entity->getTransform().getRot()), m_speed * delta);
		}
	}

	void FreeMove::move(const maths::Vector3f &axis, float amount)
	{
		m_entity->getTransform().translate(axis * amount);
	}

}