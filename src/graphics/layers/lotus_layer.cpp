#include "lotus_layer.hpp"

const Layer *Layer::CURRENT;

Layer::~Layer()
{
	delete m_renderer;
}

void Layer::render()
{
	bind();
	
	for (auto it = m_children.begin(); it < m_children.end(); it++)
	{
		(*it)->submitToRenderer(m_renderer);
	}
	
	m_renderer->render();
}

void Layer::bind() const
{
	CURRENT = this;
}

Layer::Layer(const mat4 &projection, IRenderer *renderer) :
	Entity(Transform()),
	m_projection(projection),
	m_renderer(renderer) {}