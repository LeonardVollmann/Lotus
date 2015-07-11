#ifndef LOTUS_FREE_LOOK_HPP_INCLUDED
#define LOTUS_FREE_LOOK_HPP_INCLUDED

#include "entitycomponent.hpp"

namespace lotus {

	class FreeLook : public EntityComponent
	{
	private:
		float m_turnSpeed;
	public:
		FreeLook(float turnSpeed);
		virtual void update(float delta) override;
	};

}

#endif