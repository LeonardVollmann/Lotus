#include "lotus_forwardrenderer.hpp"
#include "../shaders/lotus_forwardambient.hpp"
#include "../shaders/lotus_forwarddirectional.hpp"
#include "../shaders/lotus_forwardpoint.hpp"
#include "../shaders/lotus_forwardspot.hpp"

void ForwardRenderer::flush()
{
	while (!m_renderQueue.empty())
	{
		const RenderableComponent *renderableComponent = m_renderQueue.front();
		renderableComponent->bind();
		
		ForwardAmbient::getInstance().bind();
		ForwardAmbient::getInstance().updateUniforms(renderableComponent->getTransform());
		glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);
		
		ForwardDirectional::getInstance().bind();
		std::vector<DirectionalLight*> directionalLights = ForwardDirectional::getInstance().getDirectionalLights();
		for (auto it = directionalLights.begin(); it < directionalLights.end(); it++)
		{
			ForwardDirectional::getInstance().setActiveDirectionalLight(&(*it));
			ForwardDirectional::getInstance().updateUniforms(renderableComponent->getTransform());
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		}
		
		ForwardPoint::getInstance().bind();
		std::vector<PointLight*> pointLights = ForwardPoint::getInstance().getPointLights();
		for (auto it = pointLights.begin(); it < pointLights.end(); it++)
		{
			ForwardPoint::getInstance().setActivePointLight(&(*it));
			ForwardPoint::getInstance().updateUniforms(renderableComponent->getTransform());
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		}
		
		ForwardSpot::getInstance().bind();
		std::vector<SpotLight*> spotLights = ForwardSpot::getInstance().getSpotLights();
		for (auto it = spotLights.begin(); it < spotLights.end(); it++)
		{
			ForwardSpot::getInstance().setActiveSpotLight(&(*it));
			ForwardSpot::getInstance().updateUniforms(renderableComponent->getTransform());
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		}
		
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		
		m_renderQueue.pop_front();
	}
}