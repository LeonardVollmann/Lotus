#ifndef LOTUS_VERTEX_HPP_INCLUDED
#define LOTUS_VERTEX_HPP_INCLUDED

#include "../maths/vector.hpp"

namespace lotus { namespace graphics {

	struct Vertex2D
	{
		maths::Vector<float, 3> position;
		maths::Vector<float, 2> texCoord;
	};

	struct Vertex3D
	{
		maths::Vector<float, 3> position;
		maths::Vector<float, 2> texCoord;
		maths::Vector<float, 3> normal;
		maths::Vector<float, 3> tangent;
	};

} }

#endif
