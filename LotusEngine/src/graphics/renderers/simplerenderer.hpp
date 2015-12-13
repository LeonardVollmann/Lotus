#pragma once

#include "irenderer.hpp"
#include "../shaders/shader.hpp"
#include "../../core/profiling.hpp"
#include "../../components/renderablecomponent.hpp"

#include <deque>

namespace lotus
{
namespace graphics
{

class SimpleRenderer : public IRenderer
{
protected:
	std::deque<const RenderableComponent *> m_renderQueue;
	Shader m_shader;
	ProfileTimer m_renderTimer;

public:
	SimpleRenderer();

	virtual void submit(const void *renderableComponent) override;
	virtual void flush() override;
};

} // namespace graphics
} // namespace lotus