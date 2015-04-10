#include "lotus_quad.hpp"

Quad::Quad(const vec2 &size, const vec4 &color) :
	Renderable(
		(GLfloat[]) {
			-size.x, -size.y, 0.0f,
			 size.x, -size.y, 0.0f,
			 size.x,  size.y, 0.0f,
			-size.x,  size.y, 0.0f
		}, 4,
		(GLushort[]) {0, 1, 2, 0, 2, 3}, 6),
	m_size(size)
{
	GLfloat colors[] {
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w
	};

	m_vao.addBuffer(new Buffer(colors, 4, 4));
}