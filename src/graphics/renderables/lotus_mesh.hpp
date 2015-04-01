#ifndef LOTUS_MESH_HPP_INCLUDED
#define LOTUS_MESH_HPP_INCLUDED

#include "lotus_renderable.hpp"
#include "../meshloading/lotus_indexedmodel.hpp"

namespace lotus { namespace graphics { 

	class Mesh : public Renderable
	{
	protected:
		const GLfloat *m_texCoords;
		const GLfloat *m_normals;
	public:
		Mesh(const GLfloat *vertices, const GLfloat *texCoords, const GLfloat *normals, GLsizei numVertices, 
			const GLushort *indices, GLsizei numIndices);
		Mesh(const IndexedModel &model);
	};

} }

#endif