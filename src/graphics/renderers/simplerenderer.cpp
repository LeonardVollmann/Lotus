#include "simplerenderer.hpp"

namespace lotus { namespace graphics { 

	void SimpleRenderer::render(const Renderable &renderable) const
	{
		glDrawElements(GL_TRIANGLES, renderable.getIndexCount(), GL_UNSIGNED_SHORT, nullptr);
	}

} }