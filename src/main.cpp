#include <iostream>
#include <cmath>

#include "maths/lotus_maths.hpp"
#include "graphics/lotus_window.hpp"
#include "graphics/lotus_shader.hpp"
#include "graphics/renderables/lotus_renderable.hpp"
#include "graphics/renderables/lotus_quad.hpp"
#include "graphics/renderables/lotus_mesh.hpp"
#include "graphics/renderers/lotus_simplerenderer.hpp"
#include "graphics/meshloading/lotus_indexedmodel.hpp"
#include "graphics/meshloading/lotus_objloader.hpp"

int main()
{
	using namespace lotus;
	using namespace lotus::maths;
	using namespace lotus::graphics;

	Window window(800, 600, "Lotus");

	IndexedModel model = OBJLoader::loadIndexedModel("dragon");
	model.finalize();
	Mesh mesh(model);

	Quad sprite(maths::vec2(0.5f, 0.5f));
	SimpleRenderer renderer;

	Shader shader("simple");
	shader.addVertexShader().addFragmentShader().compile();
	shader.addUniform("pr_matrix");
	shader.addUniform("vw_matrix");
	shader.addUniform("ml_matrix");
	shader.addUniform("u_color");

	mat4 perspective = mat4::perspective(70.0f, 800 / 600, 0.001f, 1000.0f);

	float count = 0;
	while (!window.isClosed())
	{
		window.clear();

		shader.bind();

		shader.setUniformMatrix4f("pr_matrix", perspective);
		shader.setUniformMatrix4f("vw_matrix", mat4(1.0f));
		shader.setUniformMatrix4f("ml_matrix", mat4::translation(vec3(0.0f, -2.5f, -6.0f)) * mat4::rotation(quat(0.0f, sinf(count) * 4, 0.0f, 1.0f).normalize()) * mat4::scale(maths::vec3(0.5f, 0.5f, 0.5f)));
		shader.setUniformVector3f("u_color", vec3(1.0f, 1.0f, 1.0f));

		mesh.render(&renderer);

		shader.unbind();

		window.update();
		count += 0.01f;
	}

	return 0;
}