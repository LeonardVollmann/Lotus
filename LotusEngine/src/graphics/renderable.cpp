#include "renderable.hpp"

namespace lotus
{
namespace graphics
{

Renderable::Renderable(const Vertex *vertices,
                       const GLushort *indices,
                       GLsizei numVertices,
                       GLsizei numIndices)
: m_numIndices(numIndices)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLushort), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(AttribLocation::Position);
	glVertexAttribPointer(AttribLocation::Position,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(Vertex),
	                      (const GLvoid *)offsetof(Vertex, position));

	glEnableVertexAttribArray(AttribLocation::TexCoord);
	glVertexAttribPointer(AttribLocation::TexCoord,
	                      2,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(Vertex),
	                      (const GLvoid *)offsetof(Vertex, texCoord));

	glEnableVertexAttribArray(AttribLocation::Normal);
	glVertexAttribPointer(AttribLocation::Normal,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(Vertex),
	                      (const GLvoid *)offsetof(Vertex, normal));

	glEnableVertexAttribArray(AttribLocation::Tangent);
	glVertexAttribPointer(AttribLocation::Tangent,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(Vertex),
	                      (const GLvoid *)offsetof(Vertex, tangent));
}

Renderable::Renderable(IndexedModel indexedModel)
: Renderable((const Vertex *)indexedModel.getVertices().data(),
             indexedModel.getIndices().data(),
             (GLsizei)indexedModel.getVertices().size(),
             (GLsizei)indexedModel.getIndices().size())
{
}

Renderable::~Renderable()
{
	glDeleteBuffers(1, &m_ibo);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void Renderable::bind() const
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

} // namespace graphics
} // namespace lotus