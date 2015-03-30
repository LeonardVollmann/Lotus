#include <iostream>

#include "maths/lotus_maths.hpp"
#include "graphics/lotus_window.hpp"
#include "graphics/lotus_shader.hpp"
#include "graphics/renderables/lotus_renderable.hpp"
#include "graphics/renderables/lotus_renderable2d.hpp"
#include "graphics/renderers/lotus_simplerenderer.hpp"

int main()
{
	using namespace lotus;
	using namespace lotus::maths;
	using namespace lotus::graphics;

	Window window(800, 600, "Lotus");

	Renderable2D sprite(maths::vec2(0.5f, 0.5f), maths::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	SimpleRenderer renderer;

	Shader shader("simple");
	shader.addVertexShader().addFragmentShader().compile();

	while (!window.isClosed())
	{
		window.clear();

		shader.bind();

		sprite.render(&renderer);

		shader.unbind();

		window.update();
	}

	return 0;
}