#ifndef LOTUS_SIMPLE_SHADER_HPP_INCLUDED
#define LOTUS_SIMPLE_SHADER_HPP_INCLUDED

#include "lotus_shader.hpp"

class SimpleShader : public Shader
{
public:
	static SimpleShader &getInstance();
private:
	SimpleShader();
	SimpleShader(SimpleShader const&) = delete;
	void operator=(SimpleShader const&) = delete;
};

#endif