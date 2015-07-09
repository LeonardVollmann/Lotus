#ifndef LOTUS_FORWARD_AMBIENT_HPP_INCLUDED
#define LOTUS_FORWARD_AMBIENT_HPP_INCLUDED

#include "lotus_shader.hpp"

class ForwardAmbient : public Shader
{
public:
	static ForwardAmbient &getInstance();
private:
	ForwardAmbient();
	ForwardAmbient(ForwardAmbient const&) = delete;
	void operator=(ForwardAmbient const&) = delete;
};

#endif