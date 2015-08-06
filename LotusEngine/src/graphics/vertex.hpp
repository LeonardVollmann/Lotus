#ifndef LOTUS_VERTEX_HPP_INCLUDED
#define LOTUS_VERTEX_HPP_INCLUDED

#include "../maths/vec3.hpp"
#include "../maths/vec2.hpp"

namespace lotus { namespace graphics {

	struct Vertex2D
	{
		maths::vec3 position;
		maths::vec2 texCoord;
	};

	struct Vertex3D
	{
		maths::vec3 position;
		maths::vec2 texCoord;
		maths::vec3 normal;
		maths::vec3 tangent;
	};

} }

#endif
