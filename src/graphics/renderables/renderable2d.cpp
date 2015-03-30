#include "renderable2d.hpp"

namespace lotus { namespace graphics {

	Renderable2D::Renderable2D(const maths::vec2 &size, const maths::vec4 &color) :
		Renderable(
			(GLfloat[]) {
				-size.x, -size.y, 0.0f,
				-size.x,  size.y, 0.0f,
				 size.x,  size.y, 0.0f,
				 size.x, -size.y, 0.0f
			}, 
			(GLfloat[]) {
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			}, 4,
			(GLushort[]) {0, 1, 2, 0, 2, 3}, 6),
		m_size(size),
		m_color(color) {}

} }