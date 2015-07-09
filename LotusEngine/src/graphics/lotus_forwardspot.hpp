#ifndef LOTUS_FORWARD_SPOT_HPP_INCLUDED
#define LOTUS_FORWARD_SPOT_HPP_INCLUDED

#include "lotus_shader.hpp"

class ForwardSpot : public Shader
{
private:
	std::vector<SpotLight*>	m_spotLights;
public:
	static ForwardSpot &getInstance();
	
	virtual ~ForwardSpot();
	
	void addSpotLight(SpotLight *pointLight);
	
	inline const std::vector<SpotLight*> &getSpotLights()	const { return m_spotLights; }
private:
	ForwardSpot();
	ForwardSpot(ForwardSpot const&) = delete;
	void operator=(ForwardSpot const&) = delete;
};

#endif