#ifndef LOTUS_CAMERA_HPP_INCLUDED
#define LOTUS_CAMERA_HPP_INCLUDED

#include "../core/lotus_entitycomponent.hpp"
#include "../maths/lotus_mat4.hpp"

class Camera : public Entity
{
public:
	static const Camera *CURRENT;
public:
	Camera();
	
	mat4 getViewMatrix() const;
	void bind() const;
};

#endif