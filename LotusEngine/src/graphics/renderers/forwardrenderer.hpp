#pragma once

#include "simplerenderer.hpp"
#include "../lighting.hpp"
#include "../../core/profiling.hpp"

#include <vector>

namespace lotus
{
namespace graphics
{

class ForwardRenderer : public SimpleRenderer
{
private:
	Shader m_ambientShader;
	Shader m_directionalShader;
	Shader m_pointShader;
	Shader m_spotShader;
	Shader m_shadowMapShader;

	Texture *m_shadowMap;

	AmbientLight m_ambientLight;
	std::vector<DirectionalLight *> m_directionalLights;
	std::vector<PointLight *> m_pointLights;
	std::vector<SpotLight *> m_spotLights;

	ProfileTimer m_renderTimer;

public:
	ForwardRenderer();
	virtual ~ForwardRenderer();

	virtual void flush() override;

	inline void setAmbientLight(const AmbientLight &ambientLight) { m_ambientLight = ambientLight; }
	inline void addDirectionalLight(DirectionalLight *directionalLight)
	{
		m_directionalLights.push_back(directionalLight);
	}
	inline void addPointLight(PointLight *pointLight) { m_pointLights.push_back(pointLight); }
	inline void addSpotLight(SpotLight *spotLight) { m_spotLights.push_back(spotLight); }
};

} // namespace graphics
} // namespace lotus