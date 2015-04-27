#include "lotus_renderablecomponent.hpp"

RenderableComponent::RenderableComponent(Renderable *renderable, Material *material) :
	m_renderable(renderable),
	m_material(material)
{}

RenderableComponent::~RenderableComponent()
{
	delete m_renderable;
	delete m_material;
}

void RenderableComponent::bind() const
{
	m_renderable->bind();
	m_material->bind();
}

void RenderableComponent::render(IRenderer *renderer) const
{
	renderer->submit(this);
}