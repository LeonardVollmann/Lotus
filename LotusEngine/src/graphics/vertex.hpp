#ifndef LOTUS_VERTEX_HPP_INCLUDED
#define LOTUS_VERTEX_HPP_INCLUDED

#include "../core/maths.hpp"

namespace lotus { namespace graphics {

	struct Vertex2D
	{
		maths::Vector3f position;
		maths::Vector2f texCoord;
	};

	struct Vertex3D
	{
		maths::Vector3f position;
		maths::Vector2f texCoord;
		maths::Vector3f normal;
		maths::Vector3f tangent;
	};

} }

#endif
