#ifndef LOTUS_LIGHTING_HPP_INCLUDED
#define LOTUS_LIGHTING_HPP_INCLUDED

#include "../scene/nodecomponent.hpp"
#include "../maths/vec3.hpp"

#include <GL/glew.h>

namespace lotus { namespace graphics {

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
		Attenuation(const maths::vec3 &attenuation);
		
		inline float getConstant()	const { return m_constant; }
		inline float getLinear()	const { return m_linear; }
		inline float getExponent()	const { return m_exponent; }
		
		inline void setConstant(float constant) { m_constant = constant; }
		inline void setLinear(float linear)		{ m_linear = linear; }
		inline void setExponent(float exponent) { m_exponent = exponent; }
	};

	class AmbientLight
	{
	public:
		static const AmbientLight *CURRENT;
	private:
		maths::vec3 m_light;
	public:
		AmbientLight(const maths::vec3 &light);
		AmbientLight(float r, float g, float b);
		
		void bind() const;
		
		inline const maths::vec3 &getLight() const { return m_light; }
	};

	class BaseLight : public NodeComponent
	{
	protected:
		maths::vec3 m_color;
		float m_intensity;
	public:
		BaseLight();
		BaseLight(const maths::vec3 &color, float intensity);
		virtual ~BaseLight() {}
		
		inline const maths::vec3 &getColor()	const { return m_color; }
		inline float getIntensity()		const { return m_intensity; }
		
		inline void setColor(const maths::vec3 &color)		{ m_color = color; }
		inline void setIntensity(float intensity)	{ m_intensity = intensity; }
	};

	class DirectionalLight : public BaseLight
	{
	public:
		static const DirectionalLight *CURRENT;
	protected:
		maths::vec3 m_direction;
	public:
		static void getUniformLocations(const Shader *shader, const char *name, GLuint *locations);
		static void setUniformValues(const Shader *shader, GLuint *locations);
		
		DirectionalLight();
		DirectionalLight(const maths::vec3 &color, float intensity, const maths::vec3 &direction);
		DirectionalLight(const maths::vec3 &direction, const BaseLight &base = BaseLight());
		virtual ~DirectionalLight() {}
		
		void bind() const;
		
		inline const maths::vec3 &getDirection() const { return m_direction; }
		
		inline void setDirection(const maths::vec3 &direction) { m_direction = direction; }
	};

	class PointLight : public BaseLight
	{
	public:
		static const PointLight *CURRENT;
	protected:
		Attenuation m_atten;
		maths::vec3 m_pos;
		float m_range;
	public:
		static void getUniformLocations(const Shader *shader, const char *name, GLuint *locations);
		static void setUniformValues(const Shader *shader, GLuint *locations);
		
		PointLight();
		PointLight(const maths::vec3 &color, float intensity, const Attenuation &atten, const maths::vec3 &pos);
		PointLight(const Attenuation &atten, const maths::vec3 &pos, const BaseLight &base = BaseLight());
		virtual ~PointLight() {}
		
		void bind() const;
		
		inline maths::vec3 &getPos()								{ return m_pos; }
		inline const maths::vec3 &getPos()					const	{ return m_pos; }
		inline const Attenuation &getAttenuation()	const	{ return m_atten; }
		inline float getRange()						const	{ return m_range; }
		
		inline void setAttenuation(const Attenuation &atten)	{ m_atten = atten; }
		inline void setPos(const maths::vec3 &pos)						{ m_pos = pos; }
		inline void setRange(float range)						{ m_range = range; }
	protected:
		static float calcRange(const PointLight &pointLight);
	};

	class SpotLight : public PointLight
	{
	public:
		static const SpotLight *CURRENT;
	private:
		maths::vec3 m_direction;
		float m_cutoff;
	public:
		static void getUniformLocations(const Shader *shader, const char *name, GLuint *locations);
		static void setUniformValues(const Shader *shader, GLuint *locations);
		
		SpotLight();
		SpotLight(const maths::vec3 &color, float intensity, const Attenuation &atten, const maths::vec3 &pos, const maths::vec3 &direction, float cutoff);
		SpotLight(const maths::vec3 &direction, float cutoff, const PointLight &pointLight = PointLight());
		virtual ~SpotLight() {}
		
		void bind() const;
		
		inline const maths::vec3 &getDirection()	const { return m_direction; }
		inline float getCutoff()			const { return m_cutoff; }
		
		inline void setDirection(const maths::vec3 &direction)		{ m_direction = direction; }
		inline void setCutoff(float cutoff)					{ m_cutoff = cutoff; }
	};

} }

#endif