#ifndef LOTUS_FORWARD_AMBIENT_HPP_INCLUDED
#define LOTUS_FORWARD_AMBIENT_HPP_INCLUDED

#include "lotus_shader.hpp"
#include "lotus_lighting.hpp"

class ForwardAmbient : public Shader
{
private:
	AmbientLight m_ambientLight;
public:
	static ForwardAmbient &getInstance();
	
	virtual void updateUniforms() const;
	
	inline const AmbientLight &getAmbientLight() const { return m_ambientLight; }
	inline void setAmbientLight(const vec3 &ambientLight)			{ m_ambientLight = AmbientLight(ambientLight); }
	inline void setAmbientLight(const AmbientLight &ambientLight)	{ m_ambientLight = ambientLight; }
private:
	ForwardAmbient();
	ForwardAmbient(ForwardAmbient const&) = delete;
	void operator=(ForwardAmbient const&) = delete;
};

#endif