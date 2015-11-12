#include "camera.hpp"
#include "../core/input.hpp"
#include "../maths/vector.hpp"
#include "../maths/quaternion.hpp"
#include "../maths/matrix.hpp"

namespace lotus { namespace graphics {

	const Camera *Camera::CURRENT;

	Camera::Camera()
	{
		bind();
	}

	maths::mat4f Camera::getViewMatrix() const
	{
		return maths::rotation<float, 4>(maths::conjugate(m_transform.getRot())) *
				maths::translation<float, 4>(m_transform.getPos() * -1.0f);
	}

	void Camera::bind() const
	{
		CURRENT = this;
	}

} }