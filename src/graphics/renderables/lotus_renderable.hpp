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

		const GLfloat *m_vertices;
		const GLushort *m_indices;
		GLsizei m_numIndices;
	public:
		Renderable(const GLfloat *vertices, GLsizei numVertices, const GLushort *indices, GLsizei indexCount);
		virtual ~Renderable() {}

		virtual void render(IRenderer *renderer) const;

		inline GLsizei getNumIndices() const { return m_numIndices; }
	};

} }

#endif