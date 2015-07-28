#include "spritecomponent.hpp"

namespace lotus { namespace graphics {

	SpriteComponent::SpriteComponent(Texture *texture) :
		m_texture(texture) {}

	void SpriteComponent::render(IRenderer *renderer) const
	{
		m_texture->bind(0);

		renderer->submit(this);
	}

} } 
