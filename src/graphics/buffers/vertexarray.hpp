#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "buffer.hpp"

#include <GL/glew.h>
#include <vector>

namespace lotus { namespace graphics {

	class VertexArray
	{
	private:
		GLuint m_id;
		std::vector<Buffer*> m_buffers;
	public:
		VertexArray();
		virtual ~VertexArray();

		void addBuffer(Buffer *buffer);

		void bind() const;
		void unbind() const;
	};

} }

#endif