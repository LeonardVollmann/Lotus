#include "forwardrenderer3d.hpp"
#include "../shaders/shaderfactory.hpp"

namespace lotus { namespace graphics {

	ForwardRenderer3D::ForwardRenderer3D() :
		m_ambientLight(0.0f) {}

	void ForwardRenderer3D::flush()
	{
		while (!m_renderQueue.empty())
		{
			const RenderableComponent<Renderable<Vertex3D>> *renderableComponent = m_renderQueue.front();
			renderableComponent->bind();
			renderableComponent->getMaterial()->bindTexture("diffuse", 0);
			renderableComponent->getMaterial()->bindTexture("normalMap", 1);
			renderableComponent->getMaterial()->bindTexture("dispMap", 2);
		
			m_ambientLight.bind();
			ShaderFactory::getForwardAmbient()->bind();
			ShaderFactory::getForwardAmbient()->updateUniforms();
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
		
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_EQUAL);
			
			ShaderFactory::getForwardDirectional()->bind();
			for (auto it = m_directionalLights.begin(); it < m_directionalLights.end(); it++)
			{
				(*it)->bind();
				ShaderFactory::getForwardDirectional()->updateUniforms();
				glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
			}
			
			ShaderFactory::getForwardPoint()->bind();
			for (auto it = m_pointLights.begin(); it < m_pointLights.end(); it++)
			{
				(*it)->bind();
				ShaderFactory::getForwardPoint()->updateUniforms();
				glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
			}
			
			ShaderFactory::getForwardSpot()->bind();
			for (auto it = m_spotLights.begin(); it < m_spotLights.end(); it++)
			{
				(*it)->bind();
				ShaderFactory::getForwardSpot()->updateUniforms();
				glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
			}
			
			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
			
			m_renderQueue.pop_front();
		}
	}

} }
