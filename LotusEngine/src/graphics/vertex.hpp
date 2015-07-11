#ifndef LOTUS_VERTEX_HPP_INCLUDED
#define LOTUS_VERTEX_HPP_INCLUDED

#include "vec3.hpp"
#include "vec2.hpp"

namespace lotus { namespace graphics {

	struct Vertex2D
	{
		maths::vec3 position;
		maths::vec2 texCoord;
		
		Vertex2D(const maths::vec3 &position, const maths::vec2 &texCoord) :
			position(position),
			texCoord(texCoord) {}
	};

	struct Vertex3D
	{
		maths::vec3 position;
		maths::vec2 texCoord;
		maths::vec3 normal;
		maths::vec3 tangent;
		
		Vertex3D(const maths::vec3 &position, const maths::vec2 &texCoord, const maths::vec3 &normal, const maths::vec3 &tangent) :
			position(position),
			texCoord(texCoord),
			normal(normal),
			tangent(tangent) {}
	};

} }

#endif