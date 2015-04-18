#ifndef LOTUS_CAMERA_HPP_INCLUDED
#define LOTUS_CAMERA_HPP_INCLUDED

#include "../core/lotus_transform.hpp"
#include "../maths/lotus_mat4.hpp"

class Camera
{
public:
	static const Camera *CURRENT;
private:
	Transform m_transform;
public:
	Camera();
	
	void update();
	mat4 getViewMatrix() const;
	void bind() const;

	inline const Transform &getTransform() const { return m_transform; }
private:
	void move(const vec3 &axis, float amount);
};

#endif