#ifndef LOTUS_FORWARD_SPOT_HPP_INCLUDED
#define LOTUS_FORWARD_SPOT_HPP_INCLUDED

#include "lotus_shader.hpp"

class ForwardSpot : public Shader
{
public:
	static ForwardSpot &getInstance();
private:
	ForwardSpot();
	ForwardSpot(ForwardSpot const&) = delete;
	void operator=(ForwardSpot const&) = delete;
};

#endif