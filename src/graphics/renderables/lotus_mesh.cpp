#include "lotus_mesh.hpp"

Mesh::Mesh(const GLfloat *vertices, const GLfloat *texCoords, const GLfloat *normals, GLsizei numVertices, 
	const GLushort *indices, GLsizei numIndices) :
	Renderable(vertices, numVertices, indices, numIndices),
	m_texCoords(texCoords),
	m_normals(normals)
{
	m_vao.addBuffer(new Buffer(texCoords, numVertices, 2));
	m_vao.addBuffer(new Buffer(normals, numVertices, 3));
}

Mesh::Mesh(const IndexedModel &model) :
	Mesh(model.getVertices().data(), model.getTexCoords().data(), model.getNormals().data(),
		model.getVertices().size() / 3, model.getIndices().data(), model.getIndices().size())
{}