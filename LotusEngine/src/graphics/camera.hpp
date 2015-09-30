#ifndef LOTUS_CAMERA_HPP_INCLUDED
#define LOTUS_CAMERA_HPP_INCLUDED

#include "../core/entity.hpp"
#include "../maths/matrix.hpp"

namespace lotus { namespace graphics {

	class Camera : public Entity
	{
	public:
		static const Camera *CURRENT;
	public:
		Camera();
		
		maths::Matrix4f getViewMatrix() const;
		void bind() const;
	};

} }

#endif