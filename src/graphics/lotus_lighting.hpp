#ifndef LOTUS_LIGHTING_HPP_INCLUDED
#define LOTUS_LIGHTING_HPP_INCLUDED

#include "../core/lotus_entitycomponent.hpp"
#include "../maths/lotus_vec3.hpp"

#define COLOR_DEPTH 256

class Attenuation
{
private:
	float m_constant;
	float m_linear;
	float m_exponent;
public:
	Attenuation(float constant, float linear, float exponent);
	Attenuation(const vec3 &attenuation);
	
	inline float getConstant()	const { return m_constant; }
	inline float getLinear()	const { return m_linear; }
	inline float getExponent()	const { return m_exponent; }
	
	inline void setConstant(float constant) { m_constant = constant; }
	inline void setLinear(float linear)		{ m_linear = linear; }
	inline void setExponent(float exponent) { m_exponent = exponent; }
};

class BaseLight : public EntityComponent
{
protected:
	vec3 m_color;
	float m_intensity;
public:
	BaseLight();
	BaseLight(const vec3 &color, float intensity);
	
	inline const vec3 &getColor()	const { return m_color; }
	inline float getIntensity()		const { return m_intensity; }
	
	inline void setColor(const vec3 &color)		{ m_color = color; }
	inline void setIntensity(float intensity)	{ m_intensity = intensity; }
};

class DirectionalLight : public BaseLight
{
protected:
	vec3 m_direction;
public:
	DirectionalLight();
	DirectionalLight(const vec3 &color, float intensity, const vec3 &direction);
	DirectionalLight(const vec3 &direction, const BaseLight &base = BaseLight());
	
	inline const vec3 &getDirection() const { return m_direction; }
	
	inline void setDirection(const vec3 &direction) { m_direction = direction; }
};

class PointLight : public BaseLight
{
protected:
	Attenuation m_atten;
	vec3 m_pos;
	float m_range;
public:
	PointLight();
	PointLight(const vec3 &color, float intensity, const Attenuation &atten, const vec3 &pos);
	PointLight(const Attenuation &atten, const vec3 &pos, const BaseLight &base = BaseLight());
	
	inline vec3 &getPos()								{ return m_pos; }
	inline const vec3 &getPos()					const	{ return m_pos; }
	inline const Attenuation &getAttenuation()	const	{ return m_atten; }
	inline float getRange()						const	{ return m_range; }
	
	inline void setAttenuation(const Attenuation &atten)	{ m_atten = atten; }
	inline void setPos(const vec3 &pos)						{ m_pos = pos; }
	inline void setRange(float range)						{ m_range = range; }
protected:
	static float calcRange(const PointLight &pointLight);
};

class SpotLight : public PointLight
{
private:
	vec3 m_direction;
	float m_cutoff;
public:
	SpotLight();
	SpotLight(const vec3 &color, float intensity, const Attenuation &atten, const vec3 &pos, const vec3 &direction, float cutoff);
	SpotLight(const vec3 &direction, float cutoff, const PointLight &pointLight = PointLight());
	
	inline const vec3 &getDirection()	const { return m_direction; }
	inline float getCutoff()			const { return m_cutoff; }
	
	inline void setDirection(const vec3 &direction)		{ m_direction = direction; }
	inline void setCutoff(float cutoff)					{ m_cutoff = cutoff; }
};

#endif