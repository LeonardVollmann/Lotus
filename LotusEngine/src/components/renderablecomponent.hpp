#pragma once

#include "../core/entitycomponent.hpp"
#include "../graphics/renderable.hpp"
#include "../graphics/material.hpp"
#include "../graphics/renderers/irenderer.hpp"

namespace lotus
{
namespace graphics
{

class RenderableComponent : public EntityComponent
{
private:
	Renderable *m_renderable;
	Material *m_material;

public:
	RenderableComponent(Renderable *renderable, Material *material);
	virtual ~RenderableComponent();

	virtual void render(IRenderer *renderer) const override;
	void bind() const;

	inline const Renderable *getRenderable() const { return m_renderable; }
	inline const Material *getMaterial() const { return m_material; }
};

} // namespace graphics
} // namespace lotus