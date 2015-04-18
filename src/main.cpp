#include <iostream>
#include <cmath>
#include <vector>

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
#include "graphics/layers/lotus_scenelayer.hpp"
#include "core/lotus_input.hpp"
#include "core/lotus_transform.hpp"
#include "core/lotus_engine.hpp"
#include "core/lotus_igame.hpp"

class TestGame : public IGame
{
private:
	Entity *m_dragon;
	Entity *m_plane;
	Camera m_camera;
	SpotLight m_spotLight;
public:
	TestGame() :
		IGame(),
		m_spotLight(PointLight(BaseLight(vec3(1.0f, 1.0f, 1.0f), 10.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -6.0f), 30.0f), vec3(m_camera.getTransform().getRot().getForward()), 0.7f) {}

	virtual ~TestGame() {}

	virtual void init() override
	{
//		glfwSwapInterval(0);
		
		Texture texture("texture.png");
		Material dragonMaterial(vec4(1.0f, 1.0f, 1.0f, 1.0f), texture, 2.0f, 32.0f);
//		Material planeMaterial(vec4(0.0f, 0.0f, 0.0f, 0.0f), texture, 1.0f, 8.0f);

		IndexedModel dragonModel = OBJLoader::loadIndexedModel("dragon");
		dragonModel.finalize();
		Mesh *dragonMesh = new Mesh(dragonModel);

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
		Mesh *planeMesh = new Mesh(planeModel);
		Transform planeTransform;

		PhongShader::getInstance().setAmbientLight(vec3(0.1f, 0.1f, 0.1f));
		DirectionalLight directionalLight(BaseLight(vec3(1.0f, 1.0f, 1.0f), 0.1f), vec3(1.0f, 1.0f, 1.0f).normalize());
		PhongShader::getInstance().setDirectionalLight(directionalLight);
		PhongShader::getInstance().setSpotLights(&m_spotLight, 1);

        m_dragon = new Entity();
		m_plane = new Entity();
		
		m_dragon->getTransform().translate(vec3(0.0f, -5.0f, -12.0f));
		m_plane->getTransform().rotate(quat(toRadians(90.0f), vec3(-1.0f, 0.0f, 0.0f)));
		
        m_dragon->addComponent(dragonMesh);
        m_plane->addComponent(planeMesh);

		SceneLayer *scene = new SceneLayer(70.0f, 800.0f / 600.0f, 0.01f, 1000.0f, &PhongShader::getInstance());
		scene->addChild(m_dragon);

		addLayer(scene);
	}

	virtual void update(double delta) override
	{
		m_root->update(delta);
		m_camera.update();
		m_spotLight.pointLight.pos = m_camera.getTransform().getPos();
		m_spotLight.direction = m_camera.getTransform().getRot().getBack();
		m_dragon->getTransform().rotate(quat(toRadians(1.5f), vec3(0.0f, 1.0f, 0.0f)));
	}

	virtual void render() override
	{
		Material material(vec4(1.0f, 1.0f, 1.0f, 1.0f), Texture("texture.png"), 2.0f, 32.0f);
		material.bind();
		for (auto it = m_layers.begin(); it < m_layers.end(); it++)
		{
			(*it)->render();
		}

	}
};

int main()
{
	Engine engine(60.0, 800, 600, "Lotus");
	TestGame game;
	engine.setGame(&game);
	engine.start();

	return 0;
}