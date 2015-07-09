#ifndef LOTUS_FORWARD_POINT_HPP_INCLUDED
#define LOTUS_FORWARD_POINT_HPP_INCLUDED

#include "lotus_shader.hpp"

class ForwardPoint : public Shader
{
public:
	static ForwardPoint &getInstance();
private:
	ForwardPoint();
	ForwardPoint(ForwardPoint const&) = delete;
	void operator=(ForwardPoint const&) = delete;
};

#endif