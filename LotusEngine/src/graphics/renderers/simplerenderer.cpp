#include "simplerenderer.hpp"
#include "../window.hpp"

namespace lotus
{
namespace graphics
{

SimpleRenderer::SimpleRenderer()
: m_shader("basic")
, m_renderTimer("SimpleRenderer Render Time")
{
}

void SimpleRenderer::submit(const void *renderableComponent)
{
	m_renderQueue.push_back((RenderableComponent *)renderableComponent);
}

void SimpleRenderer::flush()
{
	m_renderTimer.start();

	Window::CURRENT->bindAsRenderTarget();
	m_shader.bind();
	while (!m_renderQueue.empty())
	{
		const RenderableComponent *renderableComponent = m_renderQueue.front();
		renderableComponent->bind();
		renderableComponent->getMaterial()->bindTexture("diffuse", 0);

		m_shader.updateUniforms();
		glDrawElements(GL_TRIANGLES,
		               renderableComponent->getRenderable()->getNumIndices(),
		               GL_UNSIGNED_SHORT,
		               nullptr);

		m_renderQueue.pop_front();
	}
	m_renderTimer.stop();
}

} // namespace graphics
} // namespace lotus