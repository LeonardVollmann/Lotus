#ifndef LOTUS_SPRITE_HPP_INCLUDED
#define LOTUS_SPRITE_HPP_INCLUDED

#include "../maths/vec3.hpp"

namespace lotus { namespace graphics {

	struct Sprite
	{
		maths::vec3 pos;
		float size;
	};

} }

#endif