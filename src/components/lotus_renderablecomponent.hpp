#ifndef LOTUS_RENDERABLE_COMPONENT_HPP_INCLUDED
#define LOTUS_RENDERABLE_COMPONENT_HPP_INCLUDED

#include "../core/lotus_entitycomponent.hpp"
#include "../graphics/lotus_material.hpp"
#include "../graphics/lotus_renderables.hpp"

class RenderableComponent : public EntityComponent
{
protected:
	Renderable	*m_renderable;
	Material	*m_material;
public:
	RenderableComponent(Renderable *renderable, Material *material);
	virtual ~RenderableComponent();
	
	virtual void bind() const;
	virtual void render(IRenderer *renderer) const override;
	
	inline const Renderable *getRenderable()	const { return m_renderable; }
	inline const Material *getMaterial()		const { return m_material; }
};

#endif