#pragma once

#include "../core/entitycomponent.hpp"

namespace lotus
{

class FreeLook : public EntityComponent
{
private:
	float m_turnSpeed;

public:
	FreeLook(float turnSpeed);
	virtual void update(float delta) override;
};

} // namespace lotus