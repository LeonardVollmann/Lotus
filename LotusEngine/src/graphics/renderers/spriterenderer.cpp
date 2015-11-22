#include "spriterenderer.hpp"
#include "../../components/spritecomponent.hpp"
#include "../../core/entity.hpp"
#include "../../maths/matrix.hpp"

#include <cstdlib>

namespace lotus
{
namespace graphics
{
/*
SpriteRenderer::SpriteRenderer()
: m_shader("sprite")
, m_renderTimer("SpriteRenderer Render Time")
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, SPRITE_RENDERER_BUFFER_VERTEX_SIZE, nullptr, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
	    0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const GLvoid *)offsetof(Vertex2D, position));
	glVertexAttribPointer(
	    1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const GLvoid *)offsetof(Vertex2D, texCoord));

	GLuint *indices = new GLuint[SPRITE_RENDERER_BUFFER_INDEX_SIZE];
	unsigned int i = 0;
	for (unsigned int j = 0; j < SPRITE_RENDERER_MAX_SPRITES; j++)
	{
		indices[j * 6 + 0] = i + 0;
		indices[j * 6 + 1] = i + 1;
		indices[j * 6 + 2] = i + 2;
		indices[j * 6 + 3] = i + 2;
		indices[j * 6 + 4] = i + 3;
		indices[j * 6 + 5] = i + 0;
		i += 4;
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             SPRITE_RENDERER_MAX_SPRITES * 6 * sizeof(GLuint),
	             indices,
	             GL_STATIC_DRAW);
	delete[] indices;
}

void SpriteRenderer::prepare()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	m_buffer = (Vertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	m_count = 0;
}

void SpriteRenderer::submit(const void *s)
{
	const SpriteComponent *spriteComponent = (const SpriteComponent *)s;

	maths::mat4f transformation = spriteComponent->getEntity()->getTransform().getTransformation();

	*m_buffer =
	    Vertex2D{transformation * maths::vec3f(-0.5f, 0.5f, 0.0f), maths::vec2f(0.0f, 1.0f)};
	m_buffer++;
	*m_buffer =
	    Vertex2D{transformation * maths::vec3f(-0.5f, -0.5f, 0.0f), maths::vec2f(0.0f, 0.0f)};
	m_buffer++;
	*m_buffer =
	    Vertex2D{transformation * maths::vec3f(0.5f, -0.5f, 0.0f), maths::vec2f(1.0f, 0.0f)};
	m_buffer++;
	*m_buffer = Vertex2D{transformation * maths::vec3f(0.5f, 0.5f, 0.0f), maths::vec2f(1.0f, 1.0f)};
	m_buffer++;

	m_count++;
}

void SpriteRenderer::flush()
{
	m_renderTimer.start();
	m_shader.bind();
	m_shader.updateUniforms();

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glDrawElements(GL_TRIANGLES, m_count * 6, GL_UNSIGNED_INT, nullptr);
	m_renderTimer.stop();
}
*/
} // namespace graphics
} // namespace lotus