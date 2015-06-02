#include "lotus_layer.hpp"

const Layer *Layer::CURRENT;

Layer::Layer(const mat4 &projection, IRenderer3D *renderer) :
	m_projection(projection),
	m_renderer(renderer) {}

Layer::~Layer()
{
	delete m_renderer;
}

void Layer::render(IRenderer3D *renderer) const
{
	bind();
	
	for (auto it = m_children.begin(); it < m_children.end(); it++)
	{
		(*it)->render(m_renderer);
	}
	
	m_renderer->flush();
}

void Layer::bind() const
{
	CURRENT = this;
}