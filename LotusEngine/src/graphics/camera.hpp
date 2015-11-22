#pragma once

#include "../core/entity.hpp"
#include "../maths/types.hpp"

namespace lotus
{
namespace graphics
{

class Camera : public Entity
{
public:
	static const Camera *CURRENT;

public:
	Camera();

	maths::mat4f getViewMatrix() const;
	void bind() const;
};

} // namespace graphics
} // namespace lotus