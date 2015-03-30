#include "lotus_renderable.hpp"
#include "../renderers/lotus_irenderer.hpp"

namespace lotus { namespace graphics {

	Renderable::Renderable(GLfloat *vertices, GLfloat *colors, GLsizei vertexCount, GLushort *indices, GLsizei indexCount) :
		m_ibo(indices, indexCount),
		m_vertices(vertices),
		m_indices(indices),
		m_indexCount(indexCount),
		m_colors(colors)
	{
		m_vao.addBuffer(new Buffer(m_vertices, vertexCount * 3, 3));
		m_vao.addBuffer(new Buffer(m_colors, vertexCount * 4, 4));
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