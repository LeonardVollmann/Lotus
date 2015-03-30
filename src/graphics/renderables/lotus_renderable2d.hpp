#ifndef LOTUS_RENDERABLE_2D_HPP_INCLUDED
#define LOTUS_RENDERABLE_2D_HPP_INCLUDED

#include "lotus_renderable.hpp"
#include "../../maths/lotus_maths.hpp"

namespace lotus { namespace graphics {

	class Renderable2D : public Renderable
	{
	private:
		maths::vec2 m_size;
		maths::vec4 m_color;
	public:
		Renderable2D(const maths::vec2 &size, const maths::vec4 &color);
		virtual ~Renderable2D() {}
	};

} }

#endif