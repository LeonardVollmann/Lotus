#ifndef LOTUS_RENDERABLE_COMPONENT_HPP_INCLUDED
#define LOTUS_RENDERABLE_COMPONENT_HPP_INCLUDED

#include "lotus_entitycomponent.hpp"
#include "lotus_renderable.hpp"
#include "lotus_material.hpp"
#include "lotus_irenderer.hpp"

template<typename RENDERABLE_T>
class RenderableComponent : public EntityComponent
{
private:
	RENDERABLE_T	*m_renderable;
	Material		*m_material;
public:
	RenderableComponent<RENDERABLE_T>(RENDERABLE_T *renderable, Material *material);
	virtual ~RenderableComponent<RENDERABLE_T>();
	
	virtual void render(IRenderer *renderer) const override;
	void bind() const;
	
	inline const RENDERABLE_T *getRenderable()	const { return m_renderable; }
	inline const Material *getMaterial()		const { return m_material; }
};

#endif