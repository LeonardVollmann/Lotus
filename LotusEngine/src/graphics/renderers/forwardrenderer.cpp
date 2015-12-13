#include "forwardrenderer.hpp"
#include "../window.hpp"

namespace lotus
{
namespace graphics
{

ForwardRenderer::ForwardRenderer()
: m_ambientShader("forward_ambient")
, m_directionalShader("forward_directional")
, m_pointShader("forward_point")
, m_spotShader("forward_spot")
, m_ambientLight(0.0f)
, m_renderTimer("ForwardRenderer Render Time")
{
	// m_shadowMap = new Texture("forward_shadowmap",
	//                           1024,
	//                           1024,
	//                           nullptr,
	//                           GL_TEXTURE_2D,
	//                           GL_NEAREST,
	//                           GL_DEPTH_COMPONENT16,
	//                           GL_DEPTH_COMPONENT,
	//                           true,
	//                           GL_DEPTH_ATTACHMENT);
}

ForwardRenderer::~ForwardRenderer()
{
	// delete m_shadowMap;
}

void ForwardRenderer::flush()
{
	m_renderTimer.start();

	Window::CURRENT->bindAsRenderTarget();
	while (!m_renderQueue.empty())
	{
		const RenderableComponent *renderableComponent = m_renderQueue.front();
		renderableComponent->bind();
		renderableComponent->getMaterial()->bindTexture("diffuse", 0);
		renderableComponent->getMaterial()->bindTexture("normalMap", 1);
		renderableComponent->getMaterial()->bindTexture("dispMap", 2);

		m_ambientLight.bind();
		m_ambientShader.bind();
		m_ambientShader.updateUniforms();
		glDrawElements(GL_TRIANGLES,
		               renderableComponent->getRenderable()->getNumIndices(),
		               GL_UNSIGNED_SHORT,
		               nullptr);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);

		m_directionalShader.bind();
		for (auto it = m_directionalLights.begin(); it < m_directionalLights.end(); it++)
		{
			(*it)->bind();
			m_directionalShader.updateUniforms();
			glDrawElements(GL_TRIANGLES,
			               renderableComponent->getRenderable()->getNumIndices(),
			               GL_UNSIGNED_SHORT,
			               nullptr);
		}

		m_pointShader.bind();
		for (auto it = m_pointLights.begin(); it < m_pointLights.end(); it++)
		{
			(*it)->bind();
			m_pointShader.updateUniforms();
			glDrawElements(GL_TRIANGLES,
			               renderableComponent->getRenderable()->getNumIndices(),
			               GL_UNSIGNED_SHORT,
			               nullptr);
		}

		m_spotShader.bind();
		for (auto it = m_spotLights.begin(); it < m_spotLights.end(); it++)
		{
			(*it)->bind();
			m_spotShader.updateUniforms();
			glDrawElements(GL_TRIANGLES,
			               renderableComponent->getRenderable()->getNumIndices(),
			               GL_UNSIGNED_SHORT,
			               nullptr);
		}

		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		m_renderQueue.pop_front();
	}
	m_renderTimer.stop();
}

} // namespace graphics
} // namespace lotus