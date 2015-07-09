#ifndef LOTUS_FORWARD_RENDERER_3D_HPP_INCLUDED
#define LOTUS_FORWARD_RENDERER_3D_HPP_INCLUDED

#include "lotus_simplerenderer3d.hpp"
#include "lotus_lighting.hpp"

#include <vector>

class ForwardRenderer3D : public SimpleRenderer3D
{
private:
	AmbientLight					m_ambientLight;
	std::vector<DirectionalLight*>	m_directionalLights;
	std::vector<PointLight*>		m_pointLights;
	std::vector<SpotLight*>			m_spotLights;
public:
	ForwardRenderer3D();
	
	virtual void flush() override;
	
	inline void setAmbientLight(const AmbientLight &ambientLight)		{ m_ambientLight = ambientLight; }
	inline void addDirectionalLight(DirectionalLight *directionalLight)	{ m_directionalLights.push_back(directionalLight); }
	inline void addPointLight(PointLight *pointLight)					{ m_pointLights.push_back(pointLight); }
	inline void addSpotLight(SpotLight *spotLight)						{ m_spotLights.push_back(spotLight); }
};

#endif