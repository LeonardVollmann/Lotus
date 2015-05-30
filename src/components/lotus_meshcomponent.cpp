#include "lotus_meshcomponent.hpp"

MeshComponent::MeshComponent(Mesh *mesh, Material *material) :
	m_mesh(mesh),
	m_material(material) {}

MeshComponent::~MeshComponent()
{
	delete m_mesh;
	delete m_material;
}

void MeshComponent::bind() const
{
	m_mesh->bind();
	m_material->bind();
}

void MeshComponent::render(IRenderer3D *renderer) const
{
	renderer->submit(this);
}