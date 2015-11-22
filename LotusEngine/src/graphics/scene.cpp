#include "scene.hpp"
#include "renderers/irenderer.hpp"

namespace lotus
{
namespace graphics
{

const Scene *Scene::CURRENT;

Scene::Scene(const maths::mat4f &projection, IRenderer *renderer)
: m_projection(projection)
, m_renderer(renderer)
{
}

Scene::~Scene()
{
	delete m_renderer;
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

	m_renderer->prepare();
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
	m_entities.push_back(std::unique_ptr<Entity>(entity));
}

} // namespace graphics
} // namespace lotus