#pragma once

#include "../maths/types.hpp"

namespace lotus
{
namespace graphics
{

struct Vertex2D
{
	maths::vec3f position;
	maths::vec2f texCoord;
};

struct Vertex3D
{
	maths::vec3f position;
	maths::vec2f texCoord;
	maths::vec3f normal;
	maths::vec3f tangent;
};

} // namespace graphics
} // namespace lotus