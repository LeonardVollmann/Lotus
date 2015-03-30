#ifndef LOTUS_BUFFER_HPP_INCLUDED
#define LOTUS_BUFFER_HPP_INCLUDED

#include <GL/glew.h>

namespace lotus { namespace graphics {

	class Buffer
	{
	private:
		GLuint m_id;
		GLuint m_numComponents;
	public:
		Buffer(float *data, GLsizei count, GLuint numComponents);
		virtual ~Buffer();

		void bind() const;
		void unbind() const;

		inline GLuint getNumComponents() const { return m_numComponents; }
	};

} }

#endif