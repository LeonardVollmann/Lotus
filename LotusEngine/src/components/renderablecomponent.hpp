#ifndef LOTUS_RENDERABLE_COMPONENT_HPP_INCLUDED
#define LOTUS_RENDERABLE_COMPONENT_HPP_INCLUDED

#include "../core/entitycomponent.hpp"
#include "../graphics/renderable.hpp"
#include "../graphics/material.hpp"
#include "../graphics/renderers/irenderer.hpp"

namespace lotus { namespace graphics {

	template<typename RENDERABLE_T>
	class RenderableComponent : public EntityComponent
	{
	public:
		RenderableComponent<RENDERABLE_T>(RENDERABLE_T *renderable, Material *material);
		virtual ~RenderableComponent<RENDERABLE_T>();

		virtual void render(IRenderer *renderer) const override;
		void bind() const;

		inline const RENDERABLE_T *getRenderable()	const { return m_renderable; }
		inline const Material *getMaterial()		const { return m_material; }
	protected:
	private:
		RENDERABLE_T	*m_renderable;
		Material		*m_material;
	};

} }

#endif