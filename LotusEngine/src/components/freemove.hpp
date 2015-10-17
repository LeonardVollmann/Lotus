#ifndef LOTUS_FREE_MOVE_HPP_INCLUDED
#define LOTUS_FREE_MOVE_HPP_INCLUDED

#include "../core/entitycomponent.hpp"
#include "../core/maths.hpp"

namespace lotus {

	class FreeMove : public EntityComponent
	{
	public:
		FreeMove(float speed);
		virtual void update(float delta) override;
	private:
		void move(const maths::Vector3f &axis, float amount);
	private:
		float m_speed;
	};

}

#endif