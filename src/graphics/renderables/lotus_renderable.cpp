#include "lotus_renderable.hpp"
#include "../renderers/lotus_irenderer.hpp"

namespace lotus { namespace graphics {

	Renderable::Renderable(const GLfloat *vertices, const GLfloat *texCoords, GLsizei numVertices, const GLushort *indices, GLsizei numIndices) :
		m_ibo(indices, numIndices),
		m_vertices(vertices),
		m_texCoords(texCoords),
		m_indices(indices),
		m_numIndices(numIndices)
	{
		m_vao.addBuffer(new Buffer(m_vertices, numVertices, 3));
		m_vao.addBuffer(new Buffer(m_texCoords, numVertices, 2));
	}

	void Renderable::render(IRenderer *renderer) const
	{
		m_vao.bind();
		m_ibo.bind();

		renderer->render(*this);

		m_vao.unbind();
		m_ibo.unbind();
	}

} }