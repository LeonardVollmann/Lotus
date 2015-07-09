#ifndef LOTUS_FORWARD_DIRECTIONAL_HPP_INCLUDED
#define LOTUS_FORWARD_DIRECTIONAL_HPP_INCLUDED

#include "lotus_shader.hpp"

#include <vector>

class ForwardDirectional : public Shader
{
private:
	std::vector<DirectionalLight*>	m_directionalLights;
public:
	static ForwardDirectional &getInstance();
	
	virtual ~ForwardDirectional();
	
	void addDirectionalLight(DirectionalLight *directionalLight);
	
	inline const std::vector<DirectionalLight*> &getDirectionalLights()	const { return m_directionalLights; }
private:
	ForwardDirectional();
	ForwardDirectional(ForwardDirectional const&) = delete;
	void operator=(ForwardDirectional const&) = delete;
};

#endif