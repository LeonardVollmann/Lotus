#ifndef LOTUS_BATCH_RENDERER_2D_HPP_INCLUDED
#define LOTUS_BATCH_RENDERER_2D_HPP_INCLUDED

#include "irenderer.hpp"
#include "../vertex.hpp"

#include <GL/glew.h>

namespace lotus { namespace graphics {

	#define BATCH_RENDERER_MAX_SPRITES			60000
	#define BATCH_RENDERER_SPRITE_SIZE			4 * sizeof(Vertex2D)
	#define BATCH_RENDERER_VERTEX_BUFFER_SIZE	BATCH_RENDERER_MAX_SPRITES * BATCH_RENDERER_SPRITE_SIZE
	#define BATCH_RENDERER_NUM_INDICES			BATCH_RENDERER_MAX_SPRITES * 6
	#define BATCH_RENDERER_INDEX_BUFFER_SIZE 	BATCH_RENDERER_NUM_INDICES * sizeof(GLuint)

	class BatchRenderer2D : public IRenderer
	{
	private:
		GLuint 			m_vao;
		GLuint 			m_vbo;
		GLuint 			m_ibo;
		Vertex2D 		*m_buffer;
		unsigned int 	m_numIndices;
	public:
		BatchRenderer2D();
		virtual ~BatchRenderer2D() {}

		virtual void prepare() override;
		virtual void submit(const void *sprite) override;
		virtual void flush() override;
	};

} }

#endif