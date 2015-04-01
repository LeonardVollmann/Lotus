#include "lotus_simplerenderer.hpp"

namespace lotus { namespace graphics { 

	void SimpleRenderer::render(const Renderable &renderable) const
	{
		glDrawElements(GL_TRIANGLES, renderable.getNumIndices(), GL_UNSIGNED_SHORT, nullptr);
	}

} }