#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "../buffers/vertexarray.hpp"
#include "../buffers/buffer.hpp"
#include "../buffers/indexbuffer.hpp"

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