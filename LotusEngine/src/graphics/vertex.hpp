#ifndef LOTUS_VERTEX_HPP_INCLUDED
#define LOTUS_VERTEX_HPP_INCLUDED

#include "../core/maths.hpp"

namespace lotus { namespace graphics {

	struct Vertex2D
	{
		maths::Vector3<float> position;
		maths::Vector2<float> texCoord;
	};

	struct Vertex3D
	{
		maths::Vector3<float> position;
		maths::Vector2<float> texCoord;
		maths::Vector3<float> normal;
		maths::Vector3<float> tangent;
	};

} }

#endif
