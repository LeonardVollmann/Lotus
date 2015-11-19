#ifndef LOTUS_RENDERABLE_HPP_INCLUDED
#define LOTUS_RENDERABLE_HPP_INCLUDED

#include "vertex.hpp"
#include "indexedmodel.hpp"

#include <GL/glew.h>
#include <string>

namespace lotus { namespace graphics {

	enum AttribLocation : GLuint
	{
		Position = 0,
		TexCoord = 1,
		Normal = 2,
		Tangent = 3
	};

	template<class VERTEX_T>
	class Renderable
	{
	public:
		Renderable(const VERTEX_T *vertices, const GLushort *indices, GLsizei numVertices, GLsizei numIndices);
		Renderable(IndexedModel indexedModel);
		virtual ~Renderable();

		void bind() const;

		inline GLsizei getNumIndices() const { return m_numIndices; }
	protected:
	private:
		void initBuffers(const VERTEX_T *vertices, const GLushort *indices, GLsizei numVertices, GLsizei numIndices);
		void addPositionAttrib();
		void addTexCoordAttrib();
		void addNormalAttrib();
		void addTangentAttrib();

		GLuint	m_vao;
		GLuint	m_vbo;
		GLuint	m_ibo;
		GLsizei	m_numIndices;
	};

} }

#endif
