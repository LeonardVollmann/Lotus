#include "lotus_buffer.hpp"

Buffer::Buffer(const GLfloat *data, GLsizei count, GLuint numComponents) :
	m_numComponents(numComponents)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, count * numComponents * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_id);
}

void Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}