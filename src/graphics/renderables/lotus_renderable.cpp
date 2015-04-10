#include "lotus_renderable.hpp"
#include "../renderers/lotus_irenderer.hpp"

Renderable::Renderable(const GLfloat *vertices, GLsizei numVertices, const GLushort *indices, GLsizei numIndices) :
	m_ibo(indices, numIndices),
	m_vertices(vertices),
	m_indices(indices),
	m_numIndices(numIndices)
{
	m_vao.addBuffer(new Buffer(m_vertices, numVertices, 3));
}

void Renderable::render(IRenderer *renderer) const
{
	m_vao.bind();
	m_ibo.bind();

	renderer->render(*this);

	m_vao.unbind();
	m_ibo.unbind();
}