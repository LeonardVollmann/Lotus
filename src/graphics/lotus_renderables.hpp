#ifndef LOTUS_RENDERABLE_HPP_INCLUDED
#define LOTUS_RENDERABLE_HPP_INCLUDED

#include "buffers/lotus_vertexarray.hpp"
#include "buffers/lotus_buffer.hpp"
#include "buffers/lotus_indexbuffer.hpp"
#include "meshloading/lotus_indexedmodel.hpp"
#include "../core/lotus_entitycomponent.hpp"

#include <GL/glew.h>

class Renderable
{
protected:
	VertexArray 	m_vao;
	IndexBuffer 	m_ibo;

	const GLfloat 	*m_vertices;
	const GLushort 	*m_indices;
	GLsizei 		m_numIndices;
public:
	Renderable(const GLfloat *vertices, GLsizei numVertices, const GLushort *indices, GLsizei numIndices);
	virtual ~Renderable() {}

	void bind() const;

	inline GLsizei getNumIndices() const { return m_numIndices; }
};

class Mesh : public Renderable
{
protected:
	const GLfloat *m_texCoords;
	const GLfloat *m_normals;
public:
	Mesh(const GLfloat *vertices, const GLfloat *texCoords, const GLfloat *normals, GLsizei numVertices, const GLushort *indices, GLsizei numIndices);
	Mesh(const IndexedModel &model);
};

class Quad : public Renderable
{
public:
	Quad(const vec2 &size, const vec4 &color);
};

class Sprite : public Renderable
{
public:
	Sprite(const vec2 &size);
};

#endif