#include "lotus_renderable.hpp"

Renderable::Renderable(const GLfloat *vertices, GLsizei numVertices, const GLushort *indices, GLsizei numIndices) :
	m_ibo(indices, numIndices),
	m_vertices(vertices),
	m_indices(indices),
	m_numIndices(numIndices)
{
	m_vao.addBuffer(new Buffer(m_vertices, numVertices, 3));
}

void Renderable::bind() const
{
	m_vao.bind();
	m_ibo.bind();
}

void Renderable::submitToRenderer(IRenderer *renderer) const
{
	renderer->submit(this);
}