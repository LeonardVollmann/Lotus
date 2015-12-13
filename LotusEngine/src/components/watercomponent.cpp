#include "watercomponent.hpp"
#include "../graphics/vertex.hpp"
#include "../maths/vector.hpp"

#include <iostream>

namespace lotus
{
namespace graphics
{

WaterComponent::WaterComponent(const maths::vec3f &pos, const maths::vec2f &size)
{
	const maths::vec2f halfSize = size / 2.0f;
	const maths::vec3f normal   = {0.0f, 1.0f, 0.0f};
	const maths::vec3f tangent  = {1.0f, 0.0f, 0.0f};

	const Vertex vertices[] = {
	    {{pos.x - halfSize.x, pos.y, pos.z - halfSize.y}, {0.0f, 0.0f}, normal, tangent},
	    {{pos.x - halfSize.x, pos.y, pos.z + halfSize.y}, {0.0f, 1.0f}, normal, tangent},
	    {{pos.x + halfSize.x, pos.y, pos.z + halfSize.y}, {1.0f, 1.0f}, normal, tangent},
	    {{pos.x + halfSize.x, pos.y, pos.z - halfSize.y}, {1.0f, 0.0f}, normal, tangent},
	};

	for (unsigned int i = 0; i < 4; i++)
	{
		std::cout << "Vertex: " << vertices[i].position.x << ", " << vertices[i].position.y << ", " << vertices[i].position.z << ", " << std::endl;
	}

	const unsigned short indices[] = {0, 1, 2, 0, 2, 3};

	m_renderable = new Renderable(vertices, indices, 4, 6);
	m_material = new Material();
}

WaterComponent::~WaterComponent()
{
	delete m_renderable;
	delete m_material;
}

void WaterComponent::update(float delta)
{
}

void WaterComponent::render(IRenderer *renderer) const
{
	renderer->submit(this);
}

void WaterComponent::bind() const
{
	m_renderable->bind();
	m_material->bind();
}

} // namespace lotus
} // namespace graphics