#ifndef LOTUS_QUAD_HPP_INCLUDED
#define LOTUS_QUAD_HPP_INCLUDED

#include "lotus_renderable.hpp"
#include "../../maths/lotus_vec2.hpp"
#include "../../maths/lotus_vec4.hpp"

namespace lotus { namespace graphics {

	class Quad : public Renderable
	{
	private:
		maths::vec2 m_size;
	public:
		Quad(const maths::vec2 &size, const maths::vec4 &color);
		virtual ~Quad() {}
	};

} }

#endif