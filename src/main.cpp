#include <iostream>
#include <cmath>

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
	shader.addUniform("pr_matrix");
	shader.addUniform("vw_matrix");
	shader.addUniform("ml_matrix");
	shader.addUniform("u_color");

	mat4 perspective = mat4::perspective(70.0f, 800 / 600, 0.001f, 1000.0f);
	mat4 ortho = mat4::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 5.0f);

	float count = 0;
	while (!window.isClosed())
	{
		window.clear();

		shader.bind();

		shader.setUniformMatrix4f("pr_matrix", perspective);
		shader.setUniformMatrix4f("vw_matrix", mat4(1.0f));
		shader.setUniformMatrix4f("ml_matrix", mat4::translation(vec3(0.0f, 0.0f, -2.0f)) * mat4::rotation(quat(sinf(count), 0.0f, cosf(count), 1.0f).normalize()));
		shader.setUniformVector3f("u_color", vec3(sinf(count), 0.5f, cosf(count)));

		sprite.render(&renderer);

		shader.unbind();

		window.update();
		count += 0.01f;
	}

	return 0;
}