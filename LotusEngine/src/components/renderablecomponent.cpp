#include "renderablecomponent.hpp"

namespace lotus { namespace graphics {

	template<typename RENDERABLE_T>
	RenderableComponent<RENDERABLE_T>::RenderableComponent(RENDERABLE_T *renderable, Material *material) :
		m_renderable(renderable),
		m_material(material) {}

	template<typename RENDERABLE_T>
	RenderableComponent<RENDERABLE_T>::~RenderableComponent()
	{
		delete m_renderable;
		delete m_material;
	}

	template<typename RENDERABLE_T>
	void RenderableComponent<RENDERABLE_T>::render() const
	{
		// renderer->submit(this);
	}

	template<typename RENDERABLE_T>
	void RenderableComponent<RENDERABLE_T>::bind() const
	{
		getTransform().bind();
		m_renderable->bind();
		m_material->bind();
	}

	template class RenderableComponent<Renderable<Vertex2D>>;
	template class RenderableComponent<Renderable<Vertex3D>>;

} }