#ifndef LOTUS_PHONG_SHADER_HPP_INCLUDED
#define LOTUS_PHONG_SHADER_HPP_INCLUDED

#include "lotus_shader.hpp"

class PhongShader : public Shader
{
private:
	constexpr static int MAX_POINT_LIGHTS = 4;
	constexpr static int MAX_SPOT_LIGHTS = 4;

	vec3 				m_ambientLight;
	DirectionalLight 	m_directionalLight;
	PointLight 			*m_pointLights;
	int 				m_numPointLights;
	SpotLight 			*m_spotLights;
	int 				m_numSpotLights;
public:
	static PhongShader &getInstance();
	
	virtual void updateUniforms() const override;

	void setPointLights(PointLight *pointLights, int numLights);
	void setSpotLights(SpotLight *spotLights, int numLights);

	inline const vec3 &getAmbientLight() 					const { return m_ambientLight; }
	inline const DirectionalLight &getDirectionalLight() 	const { return m_directionalLight; }

	inline void setAmbientLight(const vec3 &ambientLight) 						{ m_ambientLight = ambientLight; }
	inline void setDirectionalLight(const DirectionalLight &directionalLight)	{ m_directionalLight = directionalLight; }
private:
	PhongShader();
	PhongShader(PhongShader const&) = delete;
	void operator=(PhongShader const&) = delete;
};

#endif