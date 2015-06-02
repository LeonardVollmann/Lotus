#ifndef LOTUS_FORWARD_POINT_HPP_INCLUDED
#define LOTUS_FORWARD_POINT_HPP_INCLUDED

#include "lotus_shader.hpp"

class ForwardPoint : public Shader
{
private:
	std::vector<PointLight*>	m_pointLights;
	PointLight					**m_activePointLight;
public:
	static ForwardPoint &getInstance();
	
	virtual ~ForwardPoint();
	
	virtual void updateUniforms(const Transform &transform) const override;
	
	void addPointLight(PointLight *pointLight);
	
	inline const std::vector<PointLight*> getPointLights()	const { return m_pointLights; }
	inline PointLight **getActivePointLight()				const { return m_activePointLight; }
	
	inline void setActivePointLight(PointLight **activePointLight) { m_activePointLight = activePointLight; }
private:
	ForwardPoint();
	ForwardPoint(ForwardPoint const&) = delete;
	void operator=(ForwardPoint const&) = delete;
};

#endif