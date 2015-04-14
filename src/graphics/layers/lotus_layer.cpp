#include "lotus_layer.hpp"

Layer::~Layer()
{
	delete m_renderer;
}

void Layer::render()
{
	for (auto it = m_children.begin(); it < m_children.end(); it++)
	{
		(*it)->submitToRenderer(m_renderer);
	}

	m_renderer->render();
}

Layer::Layer(const mat4 &projection, IRenderer *renderer, Shader *shader) :
	Entity(Transform()),
	m_projection(projection),
	m_renderer(renderer),
	m_shader(shader) {}