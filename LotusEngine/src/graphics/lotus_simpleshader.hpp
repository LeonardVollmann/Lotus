#ifndef LOTUS_SIMPLE_SHADER_HPP_INCLUDED
#define LOTUS_SIMPLE_SHADER_HPP_INCLUDED

#include "lotus_shader.hpp"

class SimpleShader : public Shader
{
public:
	static SimpleShader &getInstance();
	
	virtual void updateUniforms() const override;
private:
	SimpleShader();
	SimpleShader(SimpleShader const&) = delete;
	void operator=(SimpleShader const&) = delete;
};

#endif