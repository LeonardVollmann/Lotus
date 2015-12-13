#include "waterrenderer.hpp"
#include "../window.hpp"

namespace lotus
{
namespace graphics
{

WaterRenderer::WaterRenderer()
: m_shader("water")
, m_renderTimer("WaterRenderer Render Time")
{
}

WaterRenderer::~WaterRenderer()
{
}

void WaterRenderer::submit(const void *waterComponent)
{
	m_renderQueue.push_back(static_cast<const WaterComponent *>(waterComponent));
}

void WaterRenderer::flush()
{
	m_renderTimer.start();
	Window::CURRENT->bindAsRenderTarget();

	m_shader.bind();
	for (auto water : m_renderQueue)
	{
		water->bind();
		m_shader.updateUniforms();
		glDrawElements(
		    GL_TRIANGLES, water->getRenderable()->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
	}
	m_renderQueue.clear();
	m_renderTimer.stop();
}

} // namespace graphics
} // namespace lotus