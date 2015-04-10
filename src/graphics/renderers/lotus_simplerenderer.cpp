#include "lotus_simplerenderer.hpp"

void SimpleRenderer::render(const Renderable &renderable) const
{
	glDrawElements(GL_TRIANGLES, renderable.getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
}