#include "lotus_quad.hpp"

namespace lotus { namespace graphics {

	Quad::Quad(const maths::vec2 &size) :
		Renderable(
			(GLfloat[]) {
				-size.x, -size.y, 0.0f,
				 size.x, -size.y, 0.0f,
				 size.x,  size.y, 0.0f,
				-size.x,  size.y, 0.0f
			},
			(GLfloat[]) {
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f
			}, 4,
			(GLushort[]) {0, 1, 2, 0, 2, 3}, 6),
		m_size(size) {}

} }