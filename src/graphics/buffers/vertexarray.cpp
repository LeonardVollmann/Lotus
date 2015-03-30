#include "vertexarray.hpp"

namespace lotus { namespace graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		for (auto it = m_buffers.begin(); it != m_buffers.end(); it++)
		{
			delete *it;
		}
		
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::addBuffer(Buffer *buffer)
	{
		GLuint index = m_buffers.size();
		m_buffers.push_back(buffer);
		
		bind();
		buffer->bind();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getNumComponents(), GL_FLOAT, GL_FALSE, 0, 0);

		buffer->unbind();
		unbind();
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

} }