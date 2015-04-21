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
#include "graphics/shaders/lotus_forwardambient.hpp"
#include "graphics/shaders/lotus_forwarddirectional.hpp"
#include "graphics/shaders/lotus_forwardpoint.hpp"
#include "graphics/shaders/lotus_forwardspot.hpp"
#include "graphics/renderables/lotus_renderable.hpp"
#include "graphics/renderables/lotus_quad.hpp"
#include "graphics/renderables/lotus_mesh.hpp"
#include "graphics/renderers/lotus_simplerenderer.hpp"
#include "graphics/renderers/lotus_phongrenderer.hpp"
#include "graphics/renderers/lotus_forwardrenderer.hpp"
#include "graphics/meshloading/lotus_indexedmodel.hpp"
#include "graphics/meshloading/lotus_objloader.hpp"
#include "graphics/layers/lotus_scenelayer.hpp"
#include "components/lotus_renderablecomponent.hpp"
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
	SpotLight *m_spotLight;
	PointLight *m_pointLights[8];
public:
	TestGame() :
		IGame(),
		m_spotLight(new SpotLight(PointLight(BaseLight(vec3(1.0f, 1.0f, 1.0f), 10.0f), Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -6.0f), 30.0f), vec3(m_camera.getTransform().getRot().getForward()), 0.7f)),
		m_pointLights{
			new PointLight(BaseLight(vec3(1.0f, 1.0f, 1.0f), 0.5f), Attenuation(0.0f, 0.0f, 1.0f), vec3(-7.0f, 0.0f, 0.0f), 8.0f),
			new PointLight(BaseLight(vec3(1.0f, 0.0f, 0.0f), 0.5f), Attenuation(0.0f, 0.0f, 1.0f), vec3(-5.0f, 0.0f, 0.0f), 8.0f),
			new PointLight(BaseLight(vec3(0.0f, 1.0f, 0.0f), 0.5f), Attenuation(0.0f, 0.0f, 1.0f), vec3(-3.0f, 0.0f, 0.0f), 8.0f),
			new PointLight(BaseLight(vec3(0.0f, 0.0f, 1.0f), 0.5f), Attenuation(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), 8.0f),
			new PointLight(BaseLight(vec3(1.0f, 1.0f, 0.0f), 0.5f), Attenuation(0.0f, 0.0f, 1.0f), vec3( 1.0f, 0.0f, 0.0f), 8.0f),
			new PointLight(BaseLight(vec3(0.0f, 1.0f, 1.0f), 0.5f), Attenuation(0.0f, 0.0f, 1.0f), vec3( 3.0f, 0.0f, 0.0f), 8.0f),
			new PointLight(BaseLight(vec3(1.0f, 0.0f, 1.0f), 0.5f), Attenuation(0.0f, 0.0f, 1.0f), vec3( 5.0f, 0.0f, 0.0f), 8.0f),
			new PointLight(BaseLight(vec3(1.0f, 1.0f, 1.0f), 0.5f), Attenuation(0.0f, 0.0f, 1.0f), vec3( 7.0f, 0.0f, 0.0f), 8.0f)
		}
	{}

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
		PhongShader::getInstance().setSpotLights(m_spotLight, 1);
		PhongShader::getInstance().setPointLights(*m_pointLights, 4);

        m_dragon = new Entity();
		m_plane = new Entity();
		
		m_dragon->getTransform().translate(vec3(0.0f, 2.0f, -7.5f));
		m_plane->getTransform().rotate(quat(toRadians(90.0f), vec3(-1.0f, 0.0f, 0.0f)));
		m_plane->getTransform().translate(vec3(0.0f, -1.0f, 0.0f));
		
        m_dragon->addComponent(new RenderableComponent(dragonMesh, new Material(vec4(1.0f, 1.0f, 1.0f, 1.0f), texture, 2.0f, 32.0f)));
		m_plane->addComponent(new RenderableComponent(planeMesh, new Material(vec4(1.0f, 1.0f, 1.0f, 1.0f), texture, 2.0f, 8.0f)));
		
		ForwardAmbient::getInstance().setAmbientLight(vec3(0.1f, 0.1f, 0.1f));
		ForwardDirectional::getInstance().addDirectionalLight(new DirectionalLight(BaseLight(vec3(1.0f, 0.0f, 0.0f), 0.3f), vec3(1.0f, 1.0f, 1.0f).normalize()));
		ForwardDirectional::getInstance().addDirectionalLight(new DirectionalLight(BaseLight(vec3(0.0f, 0.0f, 1.0f), 0.3f), vec3(-1.0f, 1.0f, -1.0f).normalize()));
		for (unsigned int i = 0; i < 8; i++)
		{
//			if (i % 2 == 0)
				ForwardPoint::getInstance().addPointLight(m_pointLights[i]);
		}
		ForwardSpot::getInstance().addSpotLight(m_spotLight);
		
		SceneLayer *scene = new SceneLayer(70.0f, 800.0f / 600.0f, 0.01f, 1000.0f, new ForwardRenderer());
//		scene->addChild(m_dragon);
		scene->addChild(m_plane);

		addLayer(scene);
	}
	
	float temp = 0.0;
	virtual void update(double delta) override
	{
		temp += 0.025;
		const float sinTemp = sinf(temp) * 7.0f;
		const float cosTemp = cosf(temp) * 7.0f;
		
		for (unsigned int i = 0; i < 8; i++)
		{
			if (i % 2 == 0) m_pointLights[i]->pos.z = sinTemp;
			else			m_pointLights[i]->pos.z = cosTemp;
		}
		
		m_root->update(delta);
		m_camera.update();
		m_spotLight->pointLight.pos = m_camera.getTransform().getPos();
		m_spotLight->direction = m_camera.getTransform().getRot().getBack();
		m_dragon->getTransform().rotate(quat(toRadians(1.5f), vec3(0.0f, 1.0f, 0.0f)));
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