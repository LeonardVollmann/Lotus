#ifndef LOTUS_FORWARD_RENDERER_3D_HPP_INCLUDED
#define LOTUS_FORWARD_RENDERER_3D_HPP_INCLUDED

#include "simplerenderer.hpp"
#include "../lighting.hpp"
#include "../../core/profiling.hpp"

#include <vector>

namespace lotus { namespace graphics {

	class ForwardRenderer3D : public SimpleRenderer3D
	{
	public:
		ForwardRenderer3D();
		
		virtual void flush() override;
		
		inline void setAmbientLight(const AmbientLight &ambientLight)		{ m_ambientLight = ambientLight; }
		inline void addDirectionalLight(DirectionalLight *directionalLight)	{ m_directionalLights.push_back(directionalLight); }
		inline void addPointLight(PointLight *pointLight)					{ m_pointLights.push_back(pointLight); }
		inline void addSpotLight(SpotLight *spotLight)						{ m_spotLights.push_back(spotLight); }
	private:
		Shader							m_ambientShader;
		Shader							m_directionalShader;
		Shader							m_pointShader;
		Shader							m_spotShader;

		AmbientLight					m_ambientLight;
		std::vector<DirectionalLight*>	m_directionalLights;
		std::vector<PointLight*>		m_pointLights;
		std::vector<SpotLight*>			m_spotLights;

		ProfileTimer					m_renderTimer;
	};

} }

#endif
