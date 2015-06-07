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
	m_material->bindTexture("diffuse", 0);
	m_material->bindTexture("normalMap", 1);
	m_material->bindTexture("dispMap", 2);
}

void MeshComponent::render(IRenderer *renderer) const
{
	renderer->submit(this);
}