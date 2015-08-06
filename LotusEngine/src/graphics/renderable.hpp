#ifndef LOTUS_RENDERABLE_HPP_INCLUDED
#define LOTUS_RENDERABLE_HPP_INCLUDED

#include "vertex.hpp"
#include "indexedmodel.hpp"

#include <GL/glew.h>
#include <string>

namespace lotus { namespace graphics {

	#define VERTEX_POSITION		0b00000001
	#define VERTEX_TEXCOORD		0b00000010
	#define VERTEX_NORMAL		0b00000100
	#define VERTEX_TANGENT		0b00001000
	#define VERTEX_TYPE_2D		VERTEX_POSITION | VERTEX_TEXCOORD
	#define VERTEX_TYPE_3D		VERTEX_TYPE_2D | VERTEX_NORMAL | VERTEX_TANGENT

	#define ATTRIB_LOCATION_POSITION	0
	#define ATTRIB_LOCATION_TEXCOORD	1
	#define ATTRIB_LOCATION_NORMAL		2
	#define ATTRIB_LOCATION_TANGENT		3

	template<class VERTEX_T>
	class Renderable
	{
	private:
		GLuint			m_vao;
		GLuint			m_vbo;
		GLuint			m_ibo;
		const VERTEX_T	*m_vertices;
		const GLushort	*m_indices;
		GLsizei			m_numVertices;
		GLsizei			m_numIndices;
	public:
		Renderable(const VERTEX_T *vertices, const GLushort *indices, GLsizei numVertices, GLsizei numIndices);
		Renderable(IndexedModel indexedModel);
		virtual ~Renderable();

		void bind() const;

		inline const VERTEX_T *getVertices()	const { return m_vertices; }
		inline const GLushort *getIndices()		const { return m_indices; }
		inline GLsizei getNumVertices()			const { return m_numVertices; }
		inline GLsizei getNumIndices()			const { return m_numIndices; }
	};

} }

#endif
