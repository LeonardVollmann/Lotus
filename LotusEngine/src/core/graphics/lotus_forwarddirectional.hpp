#ifndef LOTUS_FORWARD_DIRECTIONAL_HPP_INCLUDED
#define LOTUS_FORWARD_DIRECTIONAL_HPP_INCLUDED

#include "lotus_shader.hpp"

#include <vector>

class ForwardDirectional : public Shader
{
private:
	std::vector<DirectionalLight*>	m_directionalLights;
	DirectionalLight				**m_activeDirectionalLight;
public:
	static ForwardDirectional &getInstance();
	
	virtual ~ForwardDirectional();
	
	virtual void updateUniforms(const Transform &transform) const override;
	
	void addDirectionalLight(DirectionalLight *directionalLight);
	
	inline const std::vector<DirectionalLight*> getDirectionalLights()	const { return m_directionalLights; }
	inline DirectionalLight **getActiveDirectionalLight()				const { return m_activeDirectionalLight; }
	
	inline void setActiveDirectionalLight(DirectionalLight **activeDirectionalLight) { m_activeDirectionalLight = activeDirectionalLight; }
private:
	ForwardDirectional();
	ForwardDirectional(ForwardDirectional const&) = delete;
	void operator=(ForwardDirectional const&) = delete;
};

#endif