#include "lotus_simplerenderer.hpp"

void SimpleRenderer::submit(const Renderable *renderable)
{
	m_renderQueue.push_back(renderable);
}

void SimpleRenderer::render()
{
	while (!m_renderQueue.empty())
	{
		const Renderable *renderable = m_renderQueue.front();

		renderable->bind();
		glDrawElements(GL_TRIANGLES, renderable->getNumIndices(), GL_UNSIGNED_SHORT, nullptr);

		m_renderQueue.pop_front();
	}
}