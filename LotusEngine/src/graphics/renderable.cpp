#include "renderable.hpp"

namespace lotus
{
namespace graphics
{

template <>
Renderable<Vertex2D>::Renderable(const Vertex2D *vertices,
                                 const GLushort *indices,
                                 GLsizei numVertices,
                                 GLsizei numIndices)
: m_numIndices(numIndices)
{
	initBuffers(vertices, indices, numVertices, numIndices);
	addPositionAttrib();
	addTexCoordAttrib();
}

template <>
Renderable<Vertex3D>::Renderable(const Vertex3D *vertices,
                                 const GLushort *indices,
                                 GLsizei numVertices,
                                 GLsizei numIndices)
: m_numIndices(numIndices)
{
	initBuffers(vertices, indices, numVertices, numIndices);
	addPositionAttrib();
	addTexCoordAttrib();
	addNormalAttrib();
	addTangentAttrib();
}

template <typename VERTEX_T>
Renderable<VERTEX_T>::Renderable(IndexedModel indexedModel)
: Renderable<VERTEX_T>((const VERTEX_T *)indexedModel.getVertices().data(),
                       indexedModel.getIndices().data(),
                       (GLsizei)indexedModel.getVertices().size(),
                       (GLsizei)indexedModel.getIndices().size())
{
}

template <typename VERTEX_T>
Renderable<VERTEX_T>::~Renderable()
{
	glDeleteBuffers(1, &m_ibo);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

template <typename VERTEX_T>
void Renderable<VERTEX_T>::bind() const
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

template <typename VERTEX_T>
void Renderable<VERTEX_T>::initBuffers(const VERTEX_T *vertices,
                                       const GLushort *indices,
                                       GLsizei numVertices,
                                       GLsizei numIndices)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(VERTEX_T), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLushort), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
}

template <typename VERTEX_T>
void Renderable<VERTEX_T>::addPositionAttrib()
{
	glEnableVertexAttribArray(AttribLocation::Position);
	glVertexAttribPointer(AttribLocation::Position,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(VERTEX_T),
	                      (const GLvoid *)offsetof(VERTEX_T, position));
}

template <typename VERTEX_T>
void Renderable<VERTEX_T>::addTexCoordAttrib()
{
	glEnableVertexAttribArray(AttribLocation::TexCoord);
	glVertexAttribPointer(AttribLocation::TexCoord,
	                      2,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(VERTEX_T),
	                      (const GLvoid *)offsetof(VERTEX_T, texCoord));
}

template <typename VERTEX_T>
void Renderable<VERTEX_T>::addNormalAttrib()
{
	glEnableVertexAttribArray(AttribLocation::Normal);
	glVertexAttribPointer(AttribLocation::Normal,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(VERTEX_T),
	                      (const GLvoid *)offsetof(Vertex3D, normal));
}

template <typename VERTEX_T>
void Renderable<VERTEX_T>::addTangentAttrib()
{
	glEnableVertexAttribArray(AttribLocation::Tangent);
	glVertexAttribPointer(AttribLocation::Tangent,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(VERTEX_T),
	                      (const GLvoid *)offsetof(Vertex3D, tangent));
}

template class Renderable<Vertex2D>;
template class Renderable<Vertex3D>;

} // namespace graphics
} // namespace lotus