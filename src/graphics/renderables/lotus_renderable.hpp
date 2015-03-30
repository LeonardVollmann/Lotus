#ifndef LOTUS_RENDERABLE_HPP_INCLUDED
#define LOTUS_RENDERABLE_HPP_INCLUDED

#include "../buffers/lotus_vertexarray.hpp"
#include "../buffers/lotus_buffer.hpp"
#include "../buffers/lotus_indexbuffer.hpp"

#include <GL/glew.h>

namespace lotus { namespace graphics {

	class IRenderer;

	class Renderable
	{
	protected:
		VertexArray m_vao;
		IndexBuffer m_ibo;

		GLfloat *m_vertices;
		GLushort *m_indices;
		GLsizei m_indexCount;
		GLfloat *m_colors;
	public:
		Renderable(GLfloat *vertices, GLfloat *colors, GLsizei vertexCount, GLushort *indices, GLsizei indexCount);
		virtual ~Renderable() {}

		virtual void render(IRenderer *renderer) const;

		inline GLsizei getIndexCount() const { return m_indexCount; }
	};

} }

#endif