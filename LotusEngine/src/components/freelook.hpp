#ifndef LOTUS_FREE_LOOK_HPP_INCLUDED
#define LOTUS_FREE_LOOK_HPP_INCLUDED

#include "../core/entitycomponent.hpp"

namespace lotus {

	class FreeLook : public EntityComponent
	{
	public:
		FreeLook(float turnSpeed);
		virtual void update(float delta) override;
	private:
		float m_turnSpeed;
	};

}

#endif