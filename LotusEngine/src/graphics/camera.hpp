#ifndef LOTUS_CAMERA_HPP_INCLUDED
#define LOTUS_CAMERA_HPP_INCLUDED

#include "../core/entity.hpp"
#include "../maths/types.hpp"

namespace lotus { namespace graphics {

	class Camera : public Entity
	{
	public:
		Camera();

		maths::mat4f getViewMatrix() const;
		void bind() const;
	public:
		static const Camera *CURRENT;
	};

} }

#endif