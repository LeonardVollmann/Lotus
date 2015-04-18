#ifndef LOTUS_INDEX_BUFFER_HPP_INCLUDED
#define LOTUS_INDEX_BUFFER_HPP_INCLUDED

#include <GL/glew.h>

class IndexBuffer
{
private:
	GLuint m_id;
public:
	IndexBuffer(const GLushort *data, GLsizei count);
	virtual ~IndexBuffer();

	void bind() const;
};

#endif