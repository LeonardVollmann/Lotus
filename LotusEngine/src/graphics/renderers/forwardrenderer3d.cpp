#include "forwardrenderer3d.hpp"

namespace lotus { namespace graphics {

	ForwardRenderer3D::ForwardRenderer3D() :
		m_ambientShader("forward3d_ambient"),
		m_directionalShader("forward3d_directional"),
		m_pointShader("forward3d_point"),
		m_spotShader("forward3d_spot"),
		m_ambientLight(0.0f) {}

	void ForwardRenderer3D::flush()
	{
		m_renderTimer.start();
		while (!m_renderQueue.empty())
		{
			const RenderableComponent<Renderable<Vertex3D>> *renderableComponent = m_renderQueue.front();
			renderableComponent->bind();
			renderableComponent->getMaterial()->bindTexture("diffuse", 0);
			renderableComponent->getMaterial()->bindTexture("normalMap", 1);
			renderableComponent->getMaterial()->bindTexture("dispMap", 2);

			m_ambientLight.bind();
			m_ambientShader.bind();
			m_ambientShader.updateUniforms();
			glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);

			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_EQUAL);

			m_directionalShader.bind();
			for (auto it = m_directionalLights.begin(); it < m_directionalLights.end(); it++)
			{
				(*it)->bind();
				m_directionalShader.updateUniforms();
				glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
			}

			m_pointShader.bind();
			for (auto it = m_pointLights.begin(); it < m_pointLights.end(); it++)
			{
				(*it)->bind();
				m_pointShader.updateUniforms();
				glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
			}

			m_spotShader.bind();
			for (auto it = m_spotLights.begin(); it < m_spotLights.end(); it++)
			{
				(*it)->bind();
				m_spotShader.updateUniforms();
				glDrawElements(GL_TRIANGLES, renderableComponent->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
			}

			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);

			m_renderQueue.pop_front();
		}
		m_renderTimer.stop();
	}

	void ForwardRenderer3D::displayProfilingInfo()
	{
		m_renderTimer.displayAndReset("ForwardRenderer3D Render Time: ");
	}

} }
