#ifndef LOTUS_PHONG_SHADER_HPP_INCLUDED
#define LOTUS_PHONG_SHADER_HPP_INCLUDED

#include "lotus_shader.hpp"
#include "../lotus_lighting.hpp"

namespace lotus { namespace graphics { 

	class PhongShader : public Shader
	{
	private:
		constexpr static int MAX_POINT_LIGHTS = 4;
		constexpr static int MAX_SPOT_LIGHTS = 4;

		maths::vec3 m_ambientLight;
		DirectionalLight m_directionalLight;
		PointLight *m_pointLights;
		int m_numPointLights;
		SpotLight *m_spotLights;
		int m_numSpotLights;
	public:
		PhongShader();

		virtual void updateUniforms(const Transform &transform, const Material &material, const Camera &camera, const maths::mat4 &projection) const override;

		void setUniformBaseLight(const std::string &uniform, const BaseLight &baseLight) const;
		void setUniformDirectionalLight(const std::string &uniform, const DirectionalLight &directionalLight) const;
		void setUniformAttenuation(const std::string &uniform, const Attenuation &attenuation) const;
		void setUniformPointLight(const std::string &uniform, const PointLight &pointLight) const;
		void setUniformSpotLight(const std::string &uniform, const SpotLight &spotLight) const;

		void setPointLights(PointLight *pointLights, int numLights);
		void setSpotLights(SpotLight *spotLights, int numLights);

		inline const maths::vec3 &getAmbientLight() const { return m_ambientLight; }
		inline const DirectionalLight &getDirectionalLight() const { return m_directionalLight; }

		inline void setAmbientLight(const maths::vec3 &ambientLight) { m_ambientLight = ambientLight; }
		inline void setDirectionalLight(const DirectionalLight &directionalLight) { m_directionalLight = directionalLight; }
	};

} }

#endif