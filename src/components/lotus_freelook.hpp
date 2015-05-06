#ifndef LOTUS_FREE_LOOK_HPP_INCLUDED
#define LOTUS_FREE_LOOK_HPP_INCLUDED

#include "../core/lotus_entitycomponent.hpp"

class FreeLook : public EntityComponent
{
private:
	float m_turnSpeed;
public:
	FreeLook(float turnSpeed);
	virtual void update(float delta) override;
};

#endif