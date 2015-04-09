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

	Texture texture("texture.png");

	IndexedModel dragonModel = OBJLoader::loadIndexedModel("dragon");
	dragonModel.finalize();
	Mesh dragon(dragonModel);
	Transform dragonTransform;
	Material dragonMaterial(vec4(1.0f, 1.0f, 1.0f, 1.0f), texture, 2.0f, 32.0f);

	const float size = 10.0f;
	IndexedModel planeModel;
	planeModel.addVertex(-size, -size, 0.0f);
	planeModel.addVertex( size, -size, 0.0f);
	planeModel.addVertex( size,  size, 0.0f);
	planeModel.addVertex(-size,  size, 0.0f);
	planeModel.addTexCoord(0.0f, 0.0f);
	planeModel.addTexCoord(1.0f, 0.0f);
	planeModel.addTexCoord(1.0f, 1.0f);
	planeModel.addTexCoord(0.0f, 1.0f);
	planeModel.addNormal(0.0f, 0.0f, 1.0f);
	planeModel.addNormal(0.0f, 0.0f, 1.0f);
	planeModel.addNormal(0.0f, 0.0f, 1.0f);
	planeModel.addNormal(0.0f, 0.0f, 1.0f);
	planeModel.addFace(0, 1, 2);
	planeModel.addFace(0, 2, 3);
	planeModel.finalize();
	Mesh plane(planeModel);
	Transform planeTransform;
	Material planeMaterial(vec4(0.0f, 0.0f, 0.0f, 0.0f), texture, 1.0f, 8.0f);

	SimpleRenderer renderer;
	Camera camera;

	mat4 perspective = mat4::perspective(70.0f, window.getAspect(), 0.001f, 1000.0f);

	PointLight pointLights[]
	{	
		PointLight(BaseLight(vec3(1.0f, 0.0f, 0.0f), 1.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3(-6.0f, 0.0f, 0.0f), 8.0f),
		PointLight(BaseLight(vec3(0.0f, 1.0f, 0.0f), 1.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3(-2.0f, 0.0f, 0.0f), 8.0f),
		PointLight(BaseLight(vec3(0.0f, 0.0f, 1.0f), 1.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3( 2.0f, 0.0f, 0.0f), 8.0f),
		PointLight(BaseLight(vec3(1.0f, 0.0f, 1.0f), 1.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3( 6.0f, 0.0f, 0.0f), 8.0f)
	};

	SpotLight spotLights[]
	{
		SpotLight(PointLight(BaseLight(vec3(1.0f, 0.0f, 1.0f), 1.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -6.0f), 8.0f), vec3(0.0f, -1.0f, 0.0f), 0.7f),
		SpotLight(PointLight(BaseLight(vec3(0.0f, 0.0f, 1.0f), 1.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -2.0f), 8.0f), vec3(0.0f, -1.0f, 0.0f), 0.7f),
		SpotLight(PointLight(BaseLight(vec3(0.0f, 1.0f, 0.0f), 1.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f,  2.0f), 8.0f), vec3(0.0f, -1.0f, 0.0f), 0.7f),
		SpotLight(PointLight(BaseLight(vec3(1.0f, 0.0f, 0.0f), 1.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f,  6.0f), 8.0f), vec3(0.0f, -1.0f, 0.0f), 0.7f)
	};

	SpotLight spotLight(PointLight(BaseLight(vec3(1.0f, 1.0f, 1.0f), 10.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -6.0f), 30.0f), vec3(camera.getTransform().getRot().getForward()), 0.7f);

	PhongShader phongShader;
	phongShader.setAmbientLight(vec3(0.1f, 0.1f, 0.1f));
	DirectionalLight directionalLight(BaseLight(vec3(1.0f, 1.0f, 1.0f), 0.1f), vec3(1.0f, 1.0f, 1.0f).normalize());
	phongShader.setDirectionalLight(directionalLight);
	phongShader.setPointLights(pointLights, 4);
	// phongShader.setSpotLights(spotLights, 4);
	phongShader.setSpotLights(&spotLight, 1);

	dragonTransform.translate(vec3(0.0f, 1.0f, -7.5f));
	planeTransform.translate(vec3(0.0f, -1.0f, 0.0f));
	planeTransform.rotate(quat(toRadians(90.0f), vec3(-1.0f, 0.0f, 0.0f)));

	float temp = 0.0f;
	while (!window.isClosed())
	{
		if (Input::getMouseButton(GLFW_MOUSE_BUTTON_1))
		{
			Input::setMouseLocked(true);
			Input::setCursorVisible(false);
		}
		if (Input::getKey(GLFW_KEY_ESCAPE))
		{
			Input::setMouseLocked(false);
			Input::setCursorVisible(true);
		}

		if (Input::getKey(GLFW_KEY_TAB)) spotLight.cutoff -= 0.007f;
		if (Input::getKey(GLFW_KEY_LEFT_SHIFT)) spotLight.cutoff += 0.007f;
		if (Input::getKey(GLFW_KEY_LEFT_ALT)) spotLight.pointLight.base.intensity -= 0.1f;
		if (Input::getKey(GLFW_KEY_LEFT_SUPER)) spotLight.pointLight.base.intensity += 0.1f;

		if (Input::getKey(GLFW_KEY_RIGHT_SUPER))
		{
			pointLights[0].base.intensity -= 0.1f;
			pointLights[1].base.intensity -= 0.1f;
			pointLights[2].base.intensity -= 0.1f;
			pointLights[3].base.intensity -= 0.1f;
		}
		if (Input::getKey(GLFW_KEY_RIGHT_ALT))
		{
			pointLights[0].base.intensity += 0.1f;
			pointLights[1].base.intensity += 0.1f;
			pointLights[2].base.intensity += 0.1f;
			pointLights[3].base.intensity += 0.1f;
		}

		temp += 0.025f;
		const float speed = 7.0f;
		const float sinTemp = sinf(temp);
		const float cosTemp = cosf(temp);

		for (unsigned int i = 0; i < 4; i++)
		{
			spotLights[i].direction.x = cosTemp;
			spotLights[i].direction.z = sinTemp;

			if (i % 2 == 0)
			{
				pointLights[i].pos.z = sinTemp * speed;
				spotLights[i].pointLight.pos.x = sinTemp * speed;
			}
			else
			{
				pointLights[i].pos.z = cosTemp * speed;
				spotLights[i].pointLight.pos.x = cosTemp * speed;
			}
		}

		spotLight.pointLight.pos = camera.getTransform().getPos();
		spotLight.direction = camera.getTransform().getRot().getBack();

		window.clear();

		dragonTransform.rotate(quat(toRadians(1.5f), vec3(0.0f, 1.0f, 0.0f)));

		phongShader.bind();

		phongShader.updateUniforms(dragonTransform, dragonMaterial, camera, perspective);
		dragon.render(&renderer);

		planeMaterial.bind();
		phongShader.updateUniforms(planeTransform, planeMaterial, camera, perspective);	
		plane.render(&renderer);
		planeMaterial.unbind();

		phongShader.unbind();

		window.update();
		perspective = mat4::perspective(70.0f, window.getAspect(), 0.001f, 1000.0f);
		camera.update();
	}

	return 0;
}