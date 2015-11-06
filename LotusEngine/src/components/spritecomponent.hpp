#ifndef LOTUS_SPRITE_COMPONENT_HPP_INCLUDED
#define LOTUS_SPRITE_COMPONENT_HPP_INCLUDED

#include "../core/entitycomponent.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/renderers/spriterenderer2d.hpp"

namespace lotus { namespace graphics {

	class SpriteComponent : public EntityComponent
	{
	private:
		Texture *m_texture;
	public:
		virtual void render(IRenderer *renderer) const override;
	};
	
} }

#endif