#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

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