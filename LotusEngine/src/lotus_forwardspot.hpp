#ifndef LOTUS_FORWARD_SPOT_HPP_INCLUDED
#define LOTUS_FORWARD_SPOT_HPP_INCLUDED

#include "lotus_shader.hpp"

class ForwardSpot : public Shader
{
private:
	std::vector<SpotLight*>	m_spotLights;
	SpotLight				**m_activeSpotLight;
public:
	static ForwardSpot &getInstance();
	
	virtual ~ForwardSpot();
	
	virtual void updateUniforms(const Transform &transform) const override;
	
	void addSpotLight(SpotLight *pointLight);
	
	inline const std::vector<SpotLight*> getSpotLights()	const { return m_spotLights; }
	inline SpotLight **getActiveSpotLight()				const { return m_activeSpotLight; }
	
	inline void setActiveSpotLight(SpotLight **activeSpotLight) { m_activeSpotLight = activeSpotLight; }
private:
	ForwardSpot();
	ForwardSpot(ForwardSpot const&) = delete;
	void operator=(ForwardSpot const&) = delete;
};

#endif