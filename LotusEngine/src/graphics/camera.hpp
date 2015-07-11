#ifndef LOTUS_CAMERA_HPP_INCLUDED
#define LOTUS_CAMERA_HPP_INCLUDED

#include "entitycomponent.hpp"
#include "mat4.hpp"

namespace lotus { namespace graphics {

	class Camera : public Entity
	{
	public:
		static const Camera *CURRENT;
	public:
		Camera();
		
		maths::mat4 getViewMatrix() const;
		void bind() const;
	};

} }

#endif