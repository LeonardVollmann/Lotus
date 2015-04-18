#ifndef LOTUS_BUFFER_HPP_INCLUDED
#define LOTUS_BUFFER_HPP_INCLUDED

#include <GL/glew.h>



class Buffer
{
private:
	GLuint m_id;
	GLuint m_numComponents;
public:
	Buffer(const GLfloat *data, GLsizei count, GLuint numComponents);
	virtual ~Buffer();

	void bind() const;

	inline GLuint getNumComponents() const { return m_numComponents; }
};



#endif