#include "lotus_scene.hpp"
#include "lotus_irenderer.hpp"

const Scene *Scene::CURRENT;

Scene::Scene(const mat4 &projection, IRenderer *renderer) :
	m_projection(projection),
	m_renderer(renderer) {}

Scene::~Scene()
{
	delete m_renderer;
	for (auto it = m_entities.begin(); it < m_entities.end(); it++)
	{
		delete *it;
	}
}

void Scene::update(double delta)
{
	for (auto it = m_entities.begin(); it < m_entities.end(); it++)
	{
		(*it)->update(delta);
	}
}

void Scene::render() const
{
	bind();
	
	for (auto it = m_entities.begin(); it < m_entities.end(); it++)
	{
		(*it)->render(m_renderer);
	}
	
	m_renderer->flush();
}

void Scene::bind() const
{
	CURRENT = this;
}

void Scene::add(Entity *entity)
{
	m_entities.push_back(entity);
}