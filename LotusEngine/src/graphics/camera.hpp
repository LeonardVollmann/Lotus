#ifndef LOTUS_CAMERA_HPP_INCLUDED
#define LOTUS_CAMERA_HPP_INCLUDED

#include "../scene/node.hpp"
#include "../maths/mat4.hpp"

namespace lotus { namespace graphics {

	class Camera : public Node
	{
	public:
		static const Camera *CURRENT;
	private:
		maths::mat4 m_projection;
	public:
		Camera(const maths::mat4 &projection);
		
		maths::mat4 getViewMatrix() const;
		void bind() const;

		inline const maths::mat4 &getProjectionMatrix() const { return m_projection; }
	};

} }

#endif