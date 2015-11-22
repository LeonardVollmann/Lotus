#pragma once

#include "../core/entitycomponent.hpp"
#include "../maths/types.hpp"

namespace lotus
{

class FreeMove : public EntityComponent
{
private:
	float m_speed;

public:
	FreeMove(float speed);
	virtual void update(float delta) override;

private:
	void move(const maths::vec3f &axis, float amount);
};

} // namespace lotus