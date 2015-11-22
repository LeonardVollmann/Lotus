#pragma once

#include "vertex.hpp"
#include "indexedmodel.hpp"

#include <GL/glew.h>
#include <string>

namespace lotus
{
namespace graphics
{

enum AttribLocation : GLuint
{
	Position = 0,
	TexCoord = 1,
	Normal   = 2,
	Tangent  = 3
};

class Renderable
{
private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	GLsizei m_numIndices;

public:
	Renderable(const Vertex *vertices,
	           const GLushort *indices,
	           GLsizei numVertices,
	           GLsizei numIndices);
	Renderable(IndexedModel indexedModel);
	virtual ~Renderable();

	void bind() const;

	inline GLsizei getNumIndices() const { return m_numIndices; }
};

} // namespace graphics
} // namespace lotus