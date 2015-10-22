#ifndef LOTUS_CAMERA_HPP_INCLUDED
#define LOTUS_CAMERA_HPP_INCLUDED

#include "../core/entity.hpp"
#include "../core/maths.hpp"

namespace lotus { namespace graphics {

	class Camera : public Entity
	{
	public:
		Camera();
		
		maths::Matrix4f getViewMatrix() const;
		void bind() const;
	public:
		static const Camera *CURRENT;
	};

} }

#endif