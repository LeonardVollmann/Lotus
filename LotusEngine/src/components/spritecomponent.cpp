#include "spritecomponent.hpp"

namespace lotus { namespace graphics {

	void SpriteComponent::render(IRenderer *renderer) const
	{
		renderer->submit(this);
	}
	
} }