#ifndef LOTUS_FREE_MOVE_HPP_INCLUDED
#define LOTUS_FREE_MOVE_HPP_INCLUDED

#include "../core/entitycomponent.hpp"
#include "../maths/vector.hpp"

namespace lotus {

	class FreeMove : public EntityComponent
	{
	private:
		float m_speed;
	public:
		FreeMove(float speed);
		virtual void update(float delta) override;
	private:
		void move(const maths::Vector3f &axis, float amount);
	};

}

#endif