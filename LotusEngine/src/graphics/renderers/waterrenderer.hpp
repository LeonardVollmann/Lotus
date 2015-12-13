#pragma once

#include "irenderer.hpp"
#include "../shaders/shader.hpp"
#include "../../core/profiling.hpp"
#include "../../components/watercomponent.hpp"

#include <vector>

namespace lotus
{
namespace graphics
{

	class WaterRenderer : public IRenderer
	{
	private:
		std::vector<const WaterComponent *> m_renderQueue;
		Shader m_shader;
		ProfileTimer m_renderTimer;
	public:
		WaterRenderer();
		virtual ~WaterRenderer();

		virtual void submit(const void *waterComponent) override;
		virtual void flush() override;
	};

} // namespace lotus
} // namespace graphics