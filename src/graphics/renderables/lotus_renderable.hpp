#ifndef LOTUS_RENDERABLE_HPP_INCLUDED
#define LOTUS_RENDERABLE_HPP_INCLUDED

#include "../buffers/lotus_vertexarray.hpp"
#include "../buffers/lotus_buffer.hpp"
#include "../buffers/lotus_indexbuffer.hpp"
#include "../../core/lotus_entitycomponent.hpp"

#include <GL/glew.h>

class Renderable : public EntityComponent
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
	void unbind() const;
	
	virtual void submitToRenderer(IRenderer *renderer) const override;
	virtual void update(double delta) override {}

	inline GLsizei getNumIndices() const { return m_numIndices; }
};

#endif