#ifndef LOTUS_FORWARD_POINT_HPP_INCLUDED
#define LOTUS_FORWARD_POINT_HPP_INCLUDED

#include "lotus_shader.hpp"

class ForwardPoint : public Shader
{
private:
	std::vector<PointLight*>	m_pointLights;
public:
	static ForwardPoint &getInstance();
	
	virtual ~ForwardPoint();
	
	void addPointLight(PointLight *pointLight);
	
	inline const std::vector<PointLight*> &getPointLights()	const { return m_pointLights; }
private:
	ForwardPoint();
	ForwardPoint(ForwardPoint const&) = delete;
	void operator=(ForwardPoint const&) = delete;
};

#endif