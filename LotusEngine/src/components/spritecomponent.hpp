#pragma once

#include "../core/entitycomponent.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/renderers/spriterenderer2d.hpp"

namespace lotus
{
namespace graphics
{

class SpriteComponent : public EntityComponent
{
private:
	// Texture *m_texture;
public:
	virtual void render(IRenderer *renderer) const override;
};

} // namespace graphics
} // namespace lotus