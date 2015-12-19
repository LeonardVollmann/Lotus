#pragma once

#include "../core/entitycomponent.hpp"
#include "../maths/types.hpp"

#include <GL/glew.h>
#include <string>

namespace lotus
{
namespace graphics
{

#define COLOR_DEPTH 256

class Shader;

class Attenuation
{
private:
	float m_constant;
	float m_linear;
	float m_exponent;

public:
	Attenuation(float constant, float linear, float exponent);
	Attenuation(const maths::vec3f &attenuation);

	inline float getConstant() const { return m_constant; }
	inline float getLinear() const { return m_linear; }
	inline float getExponent() const { return m_exponent; }

	inline void setConstant(float constant) { m_constant = constant; }
	inline void setLinear(float linear) { m_linear = linear; }
	inline void setExponent(float exponent) { m_exponent = exponent; }
};

class AmbientLight
{
public:
	static const AmbientLight *CURRENT;

private:
	maths::vec3f m_light;

public:
	static void
	getUniformLocations(const Shader *shader, const std::string &name, GLuint *locations);
	static void setUniformValues(const Shader *shader, GLuint *locations);

	AmbientLight(const maths::vec3f &light);
	AmbientLight(float r, float g, float b);

	void bind() const;

	inline const maths::vec3f &getLight() const { return m_light; }
};

class BaseLight : public EntityComponent
{
protected:
	maths::vec3f m_color;
	float m_intensity;

public:
	BaseLight();
	BaseLight(const maths::vec3f &color, float intensity);
	virtual ~BaseLight() {}

	inline const maths::vec3f &getColor() const { return m_color; }
	inline float getIntensity() const { return m_intensity; }

	inline void setColor(const maths::vec3f &color) { m_color = color; }
	inline void setIntensity(float intensity) { m_intensity = intensity; }
};

class DirectionalLight : public BaseLight
{
public:
	static const DirectionalLight *CURRENT;

protected:
	maths::vec3f m_direction;

public:
	static void
	getUniformLocations(const Shader *shader, const std::string &name, GLuint *locations);
	static void setUniformValues(const Shader *shader, GLuint *locations);

	DirectionalLight();
	DirectionalLight(const maths::vec3f &color, float intensity, const maths::vec3f &direction);
	DirectionalLight(const maths::vec3f &direction, const BaseLight &base = BaseLight());
	virtual ~DirectionalLight() {}

	void bind() const;

	inline const maths::vec3f &getDirection() const { return m_direction; }

	inline void setDirection(const maths::vec3f &direction) { m_direction = direction; }
};

class PointLight : public BaseLight
{
public:
	static const PointLight *CURRENT;

protected:
	Attenuation m_atten;
	maths::vec3f m_pos;
	float m_range;

public:
	static void
	getUniformLocations(const Shader *shader, const std::string &name, GLuint *locations);
	static void setUniformValues(const Shader *shader, GLuint *locations);

	PointLight();
	PointLight(const maths::vec3f &color,
	           float intensity,
	           const Attenuation &atten,
	           const maths::vec3f &pos);
	PointLight(const Attenuation &atten,
	           const maths::vec3f &pos,
	           const BaseLight &base = BaseLight());
	virtual ~PointLight() {}

	void bind() const;

	inline maths::vec3f &getPos() { return m_pos; }
	inline const maths::vec3f &getPos() const { return m_pos; }
	inline const Attenuation &getAttenuation() const { return m_atten; }
	inline float getRange() const { return m_range; }

	inline void setAttenuation(const Attenuation &atten) { m_atten = atten; }
	inline void setPos(const maths::vec3f &pos) { m_pos = pos; }
	inline void setRange(float range) { m_range = range; }
protected:
	static float calcRange(const PointLight &pointLight);
};

class SpotLight : public PointLight
{
public:
	static const SpotLight *CURRENT;

private:
	maths::vec3f m_direction;
	float m_cutoff;

public:
	static void
	getUniformLocations(const Shader *shader, const std::string &name, GLuint *locations);
	static void setUniformValues(const Shader *shader, GLuint *locations);

	SpotLight();
	SpotLight(const maths::vec3f &color,
	          float intensity,
	          const Attenuation &atten,
	          const maths::vec3f &pos,
	          const maths::vec3f &direction,
	          float cutoff);
	SpotLight(const maths::vec3f &direction,
	          float cutoff,
	          const PointLight &pointLight = PointLight());
	virtual ~SpotLight() {}

	void bind() const;

	inline const maths::vec3f &getDirection() const { return m_direction; }
	inline float getCutoff() const { return m_cutoff; }

	inline void setDirection(const maths::vec3f &direction) { m_direction = direction; }
	inline void setCutoff(float cutoff) { m_cutoff = cutoff; }
};

} // namespace graphics
} // namespace lotus