#include <iostream>
#include <cmath>

#include "maths/lotus_maths.hpp"
#include "graphics/lotus_window.hpp"
#include "graphics/lotus_lighting.hpp"
#include "graphics/lotus_texture.hpp"
#include "graphics/lotus_camera.hpp"
#include "graphics/lotus_material.hpp"
#include "graphics/shaders/lotus_shader.hpp"
#include "graphics/shaders/lotus_simpleshader.hpp"
#include "graphics/shaders/lotus_phongshader.hpp"
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
	Transform transform;
	Texture texture("texture.png");
	Material material(vec4(0.25f, 0.0f, 1.0f, 1.0f), texture, 2.0f, 32.0f);

	SimpleRenderer renderer;
	Camera camera;

	quat rot(0.0f, 0.0f, 0.0f, 1.0f);
	mat4 perspective = mat4::perspective(70.0f, window.getAspect(), 0.001f, 1000.0f);

	PhongShader phongShader;
	DirectionalLight directionalLight(BaseLight(vec3(1.0f, 1.0f, 1.0f), 0.5f), vec3(1.0f, 1.0f, 1.0f).normalize());
	phongShader.setDirectionalLight(directionalLight);

	transform.translate(vec3(0.0f, -4.0f, 0.0f));

	while (!window.isClosed())
	{
		window.clear();

		transform.rotate(quat(toRadians(1.5f), vec3(0.0f, 1.0f, 0.0f)));

		phongShader.bind();
		phongShader.updateUniforms(transform, material, camera, perspective);

		mesh.render(&renderer);

		phongShader.unbind();

		window.update();
		camera.update();
	}

	return 0;
}