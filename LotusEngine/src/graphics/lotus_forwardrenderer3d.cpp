#include "lotus_forwardrenderer3d.hpp"
#include "lotus_forwardambient.hpp"
#include "lotus_forwarddirectional.hpp"
#include "lotus_forwardpoint.hpp"
#include "lotus_forwardspot.hpp"

void ForwardRenderer3D::flush()
{
	while (!m_renderQueue.empty())
	{
		const RenderableComponent<Renderable<Vertex3D>> *renderableComponent = m_renderQueue.front();
		renderableComponent->bind();
		renderableComponent->getMaterial()->bindTexture("diffuse", 0);
		renderableComponent->getMaterial()->bindTexture("normalMap", 1);
		renderableComponent->getMaterial()->bindTexture("dispMap", 2);
	
		ForwardAmbient::getInstance().bind();
		ForwardAmbient::getInstance().updateUniforms();
		glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
	
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);
		
		ForwardDirectional::getInstance().bind();
		const std::vector<DirectionalLight*> &directionalLights = ForwardDirectional::getInstance().getDirectionalLights();
		for (auto it = directionalLights.begin(); it < directionalLights.end(); it++)
		{
			(*it)->bind();
			ForwardDirectional::getInstance().updateUniforms();
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		}
		
		ForwardPoint::getInstance().bind();
		const std::vector<PointLight*> &pointLights = ForwardPoint::getInstance().getPointLights();
		for (auto it = pointLights.begin(); it < pointLights.end(); it++)
		{
			(*it)->bind();
			ForwardPoint::getInstance().updateUniforms();
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		}
		
		ForwardSpot::getInstance().bind();
		const std::vector<SpotLight*> &spotLights = ForwardSpot::getInstance().getSpotLights();
		for (auto it = spotLights.begin(); it < spotLights.end(); it++)
		{
			(*it)->bind();
			ForwardSpot::getInstance().updateUniforms();
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		}
		
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		
		m_renderQueue.pop_front();
	}
}