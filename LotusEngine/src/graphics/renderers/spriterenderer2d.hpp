#ifndef LOTUS_SPRITE_RENDERER_2D_HPP_INCLUDED
#define LOTUS_SPRITE_RENDERER_2D_HPP_INCLUDED

#include "irenderer.hpp"
#include "../vertex.hpp"
#include "../shader.hpp"
#include "../../core/profiling.hpp"

#include <GL/glew.h>

#define SPRITE_RENDERER_MAX_SPRITES 40000
#define SPRITE_RENDERER_BUFFER_INDEX_SIZE SPRITE_RENDERER_MAX_SPRITES * 6
#define SPRITE_RENDERER_BUFFER_VERTEX_SIZE SPRITE_RENDERER_MAX_SPRITES * 4 * sizeof(Vertex2D)

namespace lotus { namespace graphics {

	class SpriteRenderer2D : public IRenderer
	{
	private:
		GLuint			m_vao;
		GLuint			m_vbo;
		GLuint			m_ibo;
		Vertex2D		*m_buffer;
		unsigned int	m_count;
		Shader			m_shader;
		ProfileTimer	m_renderTimer;
	public:
		SpriteRenderer2D();
		
		virtual void prepare() override;
		virtual void submit(const void *s) override;
		virtual void flush() override;
	};
	
} }

#endif