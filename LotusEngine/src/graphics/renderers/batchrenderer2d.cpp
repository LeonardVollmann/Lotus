#include "batchrenderer2d.hpp"
#include "../shaders/shaderfactory.hpp"
#include "../../maths/mat4.hpp"
#include "../../core/entity.hpp"
#include "../../components/spritecomponent.hpp"

#include <cstdlib>

namespace lotus { namespace graphics{

	BatchRenderer2D::BatchRenderer2D() :
		m_numIndices(0)
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const GLvoid*) offsetof(Vertex2D, position));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const GLvoid*) offsetof(Vertex2D, texCoord));

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, BATCH_RENDERER_VERTEX_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		GLuint *indices = new GLuint[BATCH_RENDERER_NUM_INDICES];
		unsigned int offset = 0;
		for (unsigned int i = 0; i < BATCH_RENDERER_NUM_INDICES; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, BATCH_RENDERER_INDEX_BUFFER_SIZE, indices, GL_STATIC_DRAW);

		delete indices;
	}

	void BatchRenderer2D::prepare() 
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		m_buffer = (Vertex2D*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		m_numIndices = 0;
	}

	void BatchRenderer2D::submit(const void *sprite) 
	{
		maths::mat4 transformation = ((const SpriteComponent*) sprite)->getEntity()->getTransform().getTransformation();
		
		m_buffer->position = transformation * maths::vec3(-0.5f, 0.5f, 0.0f);
		m_buffer->texCoord = maths::vec2(0.0f, 1.0f);
		m_buffer++;

		m_buffer->position = transformation * maths::vec3(-0.5f, -0.5f, 0.0f);
		m_buffer->texCoord = maths::vec2(0.0f, 0.0f);
		m_buffer++;

		m_buffer->position = transformation * maths::vec3(0.5f, -0.5f, 0.0f);
		m_buffer->texCoord = maths::vec2(1.0f, 0.0f);
		m_buffer++;

		m_buffer->position = transformation * maths::vec3(0.5f, 0.5f, 0.0f);
		m_buffer->texCoord = maths::vec2(1.0f, 1.0f);
		m_buffer++;

		m_numIndices += 6;
	}

	void BatchRenderer2D::flush() 
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);

		ShaderFactory::getBatch2D()->bind();
		ShaderFactory::getBatch2D()->updateUniforms();

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);
	}

} }
