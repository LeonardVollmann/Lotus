#include "lotus_renderables.hpp"

Renderable::Renderable(const GLfloat *vertices, GLsizei numVertices, const GLushort *indices, GLsizei numIndices) :
	m_ibo(indices, numIndices),
	m_vertices(vertices),
	m_indices(indices),
	m_numIndices(numIndices)
{
	m_vao.addBuffer(new Buffer(m_vertices, numVertices, 3));
}

void Renderable::bind() const
{
	m_vao.bind();
	m_ibo.bind();
}

Mesh::Mesh(const GLfloat *vertices, const GLfloat *texCoords, const GLfloat *normals, GLsizei numVertices, const GLushort *indices, GLsizei numIndices) :
	Renderable(vertices, numVertices, indices, numIndices),
	m_texCoords(texCoords),
	m_normals(normals)
{
	m_vao.addBuffer(new Buffer(texCoords, numVertices, 2));
	m_vao.addBuffer(new Buffer(normals, numVertices, 3));
}

Mesh::Mesh(const IndexedModel &model) :
	Mesh(model.getVertices().data(), model.getTexCoords().data(), model.getNormals().data(), (GLsizei) model.getVertices().size() / 3, model.getIndices().data(), (GLsizei) model.getIndices().size()) {}

Quad::Quad(const vec2 &size, const vec4 &color) :
	Renderable((GLfloat[]) {
		-size.x, -size.y, 0.0f,
		 size.x, -size.y, 0.0f,
		 size.x,  size.y, 0.0f,
		-size.x,  size.y, 0.0f }, 4, (GLushort[]) {0, 1, 2, 0, 2, 3}, 6)
{
	GLfloat colors[] {
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w
	};
	
	m_vao.addBuffer(new Buffer(colors, 4, 4));
}

Sprite::Sprite(const vec2 &size) :
	Renderable((GLfloat[]) {
		-size.x, -size.y, 0.0f,
		 size.x, -size.y, 0.0f,
		 size.x,  size.y, 0.0f,
		-size.x,  size.y, 0.0f  }, 4, (GLushort[]) {0, 1, 2, 0, 2, 3}, 6)
{
	GLfloat texCoords[] {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
	};
	
	GLfloat normals[] {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};
	
	m_vao.addBuffer(new Buffer(texCoords, 4, 2));
	m_vao.addBuffer(new Buffer(normals, 4, 3));
}