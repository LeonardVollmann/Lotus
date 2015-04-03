#include <iostream>
#include <cmath>

#include "maths/lotus_maths.hpp"
#include "graphics/lotus_window.hpp"
#include "graphics/lotus_shader.hpp"
#include "graphics/lotus_lighting.hpp"
#include "graphics/renderables/lotus_renderable.hpp"
#include "graphics/renderables/lotus_quad.hpp"
#include "graphics/renderables/lotus_mesh.hpp"
#include "graphics/renderers/lotus_simplerenderer.hpp"
#include "graphics/meshloading/lotus_indexedmodel.hpp"
#include "graphics/meshloading/lotus_objloader.hpp"
#include "core/lotus_input.hpp"
#include "core/lotus_transform.hpp"

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

	Shader shader("phong");
	shader.addVertexShader().addFragmentShader().compile();
	shader.addUniform("pr_matrix");
	shader.addUniform("vw_matrix");
	shader.addUniform("ml_matrix");
	shader.addUniform("baseColor");
	shader.addUniform("ambientLight");
	shader.addUniform("directionalLight.base.color");
	shader.addUniform("directionalLight.base.intensity");
	shader.addUniform("directionalLight.direction");

	mat4 perspective = mat4::perspective(70.0f, window.getAspect(), 0.001f, 1000.0f);

	float count = 0;
	while (!window.isClosed())
	{
		std::cout << Input::getKey(GLFW_KEY_SPACE) << std::endl;

		window.clear();

		shader.bind();

		perspective = mat4::perspective(70.0f, window.getAspect(), 0.001f, 1000.0f);
		shader.setUniformMat4("pr_matrix", perspective);
		shader.setUniformMat4("vw_matrix", mat4(1.0f));
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0.0f, -2.5f, -6.0f)) * mat4::rotation(quat(0.0f, sinf(count) * 4, 0.0f, 1.0f).normalize()) * mat4::scale(maths::vec3(0.5f, 0.5f, 0.5f)));
		shader.setUniformVec4("baseColor", vec4(0.53f, 0.0f, 0.54f, 1.0f));
		shader.setUniformVec3("ambientLight", vec3(0.2f, 0.2f, 0.2f));
		shader.setUniformDirectionalLight("directionalLight", DirectionalLight(vec3(1.0f, 1.0f, 1.0f), 0.8f, vec3(1.0f, 1.0f, 1.0f).normalize()));

		mesh.render(&renderer);

		shader.unbind();

		window.update();
		count += 0.01f;
	}

	return 0;
}