#ifndef LOTUS_FREE_MOVE_HPP_INCLUDED
#define LOTUS_FREE_MOVE_HPP_INCLUDED

#include "entitycomponent.hpp"

namespace lotus {

	class FreeMove : public EntityComponent
	{
	private:
		float m_speed;
	public:
		FreeMove(float speed);
		virtual void update(float delta) override;
	private:
		void move(const maths::vec3 &axis, float amount);
	};

}

#endif