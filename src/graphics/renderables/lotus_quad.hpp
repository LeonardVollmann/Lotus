#ifndef LOTUS_QUAD_HPP_INCLUDED
#define LOTUS_QUAD_HPP_INCLUDED

#include "lotus_renderable.hpp"
#include "../../maths/lotus_vec2.hpp"
#include "../../maths/lotus_vec4.hpp"

class Quad : public Renderable
{
private:
	vec2 m_size;
public:
	Quad(const vec2 &size, const vec4 &color);
	virtual ~Quad() {}
};

#endif