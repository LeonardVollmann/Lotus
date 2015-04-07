#ifndef LOTUS_QUAD_HPP_INCLUDED
#define LOTUS_QUAD_HPP_INCLUDED

#include "lotus_renderable.hpp"
#include "../../maths/lotus_maths.hpp"

namespace lotus { namespace graphics {

	class Quad : public Renderable
	{
	private:
		maths::vec2 m_size;
	public:
		Quad(const maths::vec2 &size);
		virtual ~Quad() {}
	};

} }

#endif