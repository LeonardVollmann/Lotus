#ifndef LOTUS_FORWARD_AMBIENT_HPP_INCLUDED
#define LOTUS_FORWARD_AMBIENT_HPP_INCLUDED

#include "lotus_shader.hpp"

class ForwardAmbient : public Shader
{
private:
	vec3 m_ambientLight;
public:
	static ForwardAmbient &getInstance();
	
	virtual void updateUniforms(const Transform &transform) const;
	
	inline const vec3 &getAmbientLight() const { return m_ambientLight; }
	inline void setAmbientLight(const vec3 &ambientLight) { m_ambientLight = ambientLight; }
private:
	ForwardAmbient();
	ForwardAmbient(ForwardAmbient const&) = delete;
	void operator=(ForwardAmbient const&) = delete;
};

#endif