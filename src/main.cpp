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
#include "graphics/lotus_renderables.hpp"
#include "graphics/renderers/lotus_simplerenderer.hpp"
#include "graphics/renderers/lotus_phongrenderer.hpp"
#include "graphics/renderers/lotus_forwardrenderer.hpp"
#include "graphics/meshloading/lotus_indexedmodel.hpp"
#include "graphics/meshloading/lotus_objloader.hpp"
#include "components/lotus_renderablecomponent.hpp"
#include "components/lotus_freemove.hpp"
#include "components/lotus_freelook.hpp"
#include "components/lotus_animation2d.hpp"
#include "core/lotus_input.hpp"
#include "core/lotus_transform.hpp"
#include "core/lotus_engine.hpp"
#include "core/lotus_igame.hpp"

class TestGame : public IGame
{
private:
	Entity *m_dragon;
	Entity *m_plane;
	Entity *m_sprite;
	Camera *m_camera;
	SpotLight *m_spotLight;
	PointLight *m_pointLights[8];
	float m_temp = 0.0f;
public:
	TestGame() :
		IGame(),
		m_camera(new Camera()),
		m_spotLight(new SpotLight(vec3(1.0f, 1.0f, 1.0f), 10.0f, Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -6.0f), vec3(m_camera->getTransform().getRot().getForward()), 0.7f)),
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
		
		std::vector<Texture*> animationFrames;
		Material *spriteMaterial = new Material();
		material->addFloat("specularIntensity", 2.0f);
		material->addFloat("specularPower", 8.0f);
		animationFrames.push_back(new Texture("animation/0.png"));
		animationFrames.push_back(new Texture("animation/1.png"));
		animationFrames.push_back(new Texture("animation/2.png"));
		
        m_dragon = new Entity();
		m_plane = new Entity();
		m_sprite = new Entity();
		
		m_camera->bind();
		m_camera->addComponent(new FreeMove(10.0f));
		m_camera->addComponent(new FreeLook(5.0f));
		add(m_camera);
		
		m_dragon->getTransform().translate(vec3(0.0f, 2.0f, -7.5f));
		m_plane->getTransform().rotate(quat(toRadians(90.0f), vec3(-1.0f, 0.0f, 0.0f)));
		m_plane->getTransform().translate(vec3(0.0f, -1.0f, 0.0f));
		m_plane->getTransform().scale(vec3(10.0f, 10.0f, 1.0f));
		m_sprite->getTransform().translate(vec3(0.0f, 2.0f, -5.0f));
		m_sprite->getTransform().scale(vec3(2.0f, 2.0f, 1.0f));
		
        m_dragon->addComponent(new RenderableComponent(new Mesh(OBJLoader::loadIndexedModel("dragon").finalize()), material));
		m_plane->addComponent(new RenderableComponent(new Sprite(vec2(1.0f, 1.0f)), material));
		m_sprite->addComponent(new Animation2D(new Sprite(vec2(1.0f, 1.0f)), spriteMaterial, animationFrames, 1.0f, true));
		
		ForwardAmbient::getInstance().setAmbientLight(vec3(0.1f, 0.1f, 0.1f));
		ForwardDirectional::getInstance().addDirectionalLight(new DirectionalLight(vec3(1.0f, 0.0f, 0.0f), 0.3f, vec3(1.0f, 1.0f, 1.0f).normalize()));
		ForwardDirectional::getInstance().addDirectionalLight(new DirectionalLight(vec3(0.0f, 0.0f, 1.0f), 0.3f, vec3(-1.0f, 1.0f, -1.0f).normalize()));
		for (unsigned int i = 0; i < 8; i++)
		{
			ForwardPoint::getInstance().addPointLight(m_pointLights[i]);
		}
		ForwardSpot::getInstance().addSpotLight(m_spotLight);
		
		Layer *scene = new Layer(mat4::perspective(70.0f, 1000.0 / 800.0f, 0.01f, 1000.0f), new ForwardRenderer());
//		scene->addChild(m_dragon);
		scene->addChild(m_plane);
		scene->addChild(m_sprite);

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