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
#include "graphics/renderers/lotus_simplerenderer3d.hpp"
#include "graphics/renderers/lotus_phongrenderer3d.hpp"
#include "graphics/renderers/lotus_forwardrenderer3d.hpp"
#include "graphics/meshloading/lotus_indexedmodel.hpp"
#include "graphics/meshloading/lotus_objloader.hpp"
#include "components/lotus_meshcomponent.hpp"
#include "components/lotus_freemove.hpp"
#include "components/lotus_freelook.hpp"
#include "core/lotus_input.hpp"
#include "core/lotus_transform.hpp"
#include "core/lotus_engine.hpp"
#include "core/lotus_igame.hpp"

class TestGame : public IGame
{
private:
	Entity *m_dragon;
	Camera *m_camera;
	SpotLight *m_spotLight;
	PointLight *m_pointLights[8];
	float m_temp = 0.0f;
public:
	TestGame() :
		IGame(),
		m_camera(new Camera()),
		m_spotLight(new SpotLight(vec3(1.0f, 1.0f, 1.0f), 15.0f, Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -6.0f), vec3(m_camera->getTransform().getRot().getForward()), 0.7f)),
		m_pointLights
		{
			new PointLight(vec3(1.0f, 1.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), vec3(-7.0f, 0.0f, 0.0f)),
			new PointLight(vec3(1.0f, 0.0f, 0.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), vec3(-5.0f, 0.0f, 0.0f)),
			new PointLight(vec3(0.0f, 1.0f, 0.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), vec3(-3.0f, 0.0f, 0.0f)),
			new PointLight(vec3(0.0f, 0.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f)),
			new PointLight(vec3(1.0f, 1.0f, 0.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), vec3( 1.0f, 0.0f, 0.0f)),
			new PointLight(vec3(0.0f, 1.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), vec3( 3.0f, 0.0f, 0.0f)),
			new PointLight(vec3(1.0f, 0.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), vec3( 5.0f, 0.0f, 0.0f)),
			new PointLight(vec3(1.0f, 1.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), vec3( 7.0f, 0.0f, 0.0f)),
		}
	{}

	virtual ~TestGame() {}
	virtual void tick() {}

	virtual void init() override
	{
//		glfwSwapInterval(0);
//		Input::setMouseLocked(true);
		
		Material *material = new Material();
		material->addFloat("specularIntensity", 2.0f);
		material->addFloat("specularPower", 32.0f);
		material->addVec4("color", vec4(0.2f, 0.2f, 0.2f, 1.0f));
		
        m_dragon = new Entity();
		
		m_camera->bind();
		m_camera->addComponent(new FreeMove(10.0f));
		m_camera->addComponent(new FreeLook(5.0f));
		add(m_camera);
		
		m_dragon->addComponent(new MeshComponent(new Mesh(OBJLoader::loadIndexedModel("dragon").finalize()), material));
		
		ForwardAmbient::getInstance().setAmbientLight(vec3(0.1f, 0.1f, 0.1f));
		ForwardDirectional::getInstance().addDirectionalLight(new DirectionalLight(vec3(1.0f, 0.0f, 0.0f), 0.3f, vec3(1.0f, 1.0f, 1.0f).normalize()));
		ForwardDirectional::getInstance().addDirectionalLight(new DirectionalLight(vec3(0.0f, 0.0f, 1.0f), 0.3f, vec3(-1.0f, 1.0f, -1.0f).normalize()));
		for (unsigned int i = 0; i < 8; i++)
		{
			ForwardPoint::getInstance().addPointLight(m_pointLights[i]);
		}
		ForwardSpot::getInstance().addSpotLight(m_spotLight);
		
		Layer *scene = new Layer(mat4::perspective(70.0f, 1000.0 / 800.0f, 0.01f, 1000.0f), new ForwardRenderer3D());
		scene->addChild(m_dragon);

		addLayer(scene);
	}
	
	virtual void update(double delta) override
	{
		m_temp += 0.025f;
		const float sinTemp = sinf(m_temp) * 7.0f;
		const float cosTemp = cosf(m_temp) * 7.0f;
		
		for (unsigned int i = 0; i < 8; i++)
		{
			if (i % 2 == 0) m_pointLights[i]->getPos().z = sinTemp;
			else			m_pointLights[i]->getPos().z = cosTemp;
		}
		
		m_root->update(delta);
		m_spotLight->setPos(m_camera->getTransform().getPos());
		m_spotLight->setDirection(m_camera->getTransform().getRot().getBack());
		m_dragon->getTransform().rotate(quat(toRadians(1.5f), vec3(0.0f, 1.0f, 0.0f)));
	}
};

int main()
{
	Engine engine(60.0, 1000, 800, "Lotus");
	TestGame game;
	engine.setGame(&game);
	engine.start();

	return 0;
}