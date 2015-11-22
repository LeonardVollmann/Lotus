#include "renderablecomponent.hpp"
#include "../core/entity.hpp"

namespace lotus
{
namespace graphics
{

RenderableComponent::RenderableComponent(Renderable *renderable, Material *material)
: m_renderable(renderable)
, m_material(material)
{
}

RenderableComponent::~RenderableComponent()
{
	delete m_renderable;
	delete m_material;
}

void RenderableComponent::render(IRenderer *renderer) const
{
	renderer->submit(this);
}

void RenderableComponent::bind() const
{
	m_entity->getTransform().bind();
	m_renderable->bind();
	m_material->bind();
}

} // namespace graphics
} // namespace lotus