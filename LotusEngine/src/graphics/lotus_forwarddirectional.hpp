#ifndef LOTUS_FORWARD_DIRECTIONAL_HPP_INCLUDED
#define LOTUS_FORWARD_DIRECTIONAL_HPP_INCLUDED

#include "lotus_shader.hpp"

#include <vector>

class ForwardDirectional : public Shader
{
public:
	static ForwardDirectional &getInstance();
private:
	ForwardDirectional();
	ForwardDirectional(ForwardDirectional const&) = delete;
	void operator=(ForwardDirectional const&) = delete;
};

#endif