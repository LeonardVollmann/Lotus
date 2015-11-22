#pragma once

#include <GL/glew.h>

namespace lotus
{
namespace graphics
{

class IRenderer
{
public:
	virtual ~IRenderer() {}

	virtual void prepare() {}
	virtual void submit(const void *object) = 0;
	virtual void flush() = 0;
};

} // namespace graphics
} // namespace lotus