#ifndef LOTUS_INDEX_BUFFER_HPP_INCLUDED
#define LOTUS_INDEX_BUFFER_HPP_INCLUDED

#include <GL/glew.h>

namespace lotus { namespace graphics {

	class IndexBuffer
	{
	private:
		GLuint m_id;
	public:
		IndexBuffer(GLushort *data, GLsizei count);
		virtual ~IndexBuffer();

		void bind() const;
		void unbind() const;
	};

} }

#endif