#ifndef LOTUS_MESH_HPP_INCLUDED
#define LOTUS_MESH_HPP_INCLUDED

#include "lotus_vertex3d.hpp"
#include "meshloading/lotus_indexedmodel.hpp"

#include <GL/glew.h>

class Mesh
{
private:
	GLuint	m_vao;
	GLuint	m_vbo;
	GLuint	m_ibo;
	GLsizei	m_numIndices;
public:
	Mesh(const Vertex3D *vertices, GLsizei numVertices, const GLushort *indices, GLsizei numIndices);
	Mesh(IndexedModel indexedModel);
	virtual ~Mesh();
	
	void bind() const;
	
	inline GLsizei getNumIndices() const { return m_numIndices; }
};

#endif