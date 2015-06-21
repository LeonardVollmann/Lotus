#include <iostream>
#include <cmath>
#include <vector>

#include <lotus.hpp>

class TestGame : public IGame
{
private:
	SpotLight *m_spotLight;
	PointLight *m_pointLights[8];
	float m_temp = 0.0f;
public:
	TestGame() :
		IGame(),
		m_spotLight(new SpotLight(vec3(1.0f, 1.0f, 1.0f), 10.0f, Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -6.0f), vec3(Transform().getRot().getForward()), 0.7f)),
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
		glfwSwapInterval(0);
//		Input::setMouseLocked(true);
		
		IndexedModel model;
		const float size = 10.0f;
		model.addPosition(-size, size, 0);
		model.addPosition(-size, -size, 0);
		model.addPosition(size, -size, 0);
		model.addPosition(size, size, 0);
		model.addTexCoord(0, 3);
		model.addTexCoord(0, 0);
		model.addTexCoord(3, 0);
		model.addTexCoord(3, 3);
		model.addFace(0, 1, 2);
		model.addFace(2, 3, 0);
		model.finalize();
		
		Material *material = new Material(new Texture("bricks.png"), vec4::ZERO, 2.0f, 32.0f, new Texture("bricks_normal.png"), new Texture("bricks_disp.png"), 0.04f);
		Material *material2 = new Material(new Texture("bricks2.png"), vec4::ZERO, 2.0f, 32.0f, new Texture("bricks2_normal.png"), new Texture("bricks2_disp.png"), 0.04f, -1.0f);
		
		Entity *plane = new Entity();
		Entity *plane2 = new Entity();
		plane->getTransform().rotate(-MATH_PI / 2.0f, vec3(1.0f, 0.0f, 0.0f));
		plane2->getTransform().rotate(-MATH_PI / 2.0f, vec3(1.0f, 0.0f, 0.0f));
		plane2->getTransform().translate(vec3(5.0f, 2.0f, 5.0f));
		plane2->getTransform().scale(vec3(0.3f, 0.3f, 0.3f));
		
		m_camera->addComponent(new FreeMove(10.0f));
		m_camera->addComponent(new FreeLook(5.0f));
		m_camera->bind();
		
		plane->addComponent(new RenderableComponent3D(new Renderable3D(model), material));
		plane2->addComponent(new RenderableComponent3D(new Renderable3D(model), material2));
		
		ForwardAmbient::getInstance().setAmbientLight(vec3(0.1f, 0.1f, 0.1f));
		ForwardDirectional::getInstance().addDirectionalLight(new DirectionalLight(vec3(1.0f, 0.0f, 0.0f), 0.3f, vec3(1.0f, 1.0f, 1.0f).normalize()));
		ForwardDirectional::getInstance().addDirectionalLight(new DirectionalLight(vec3(0.0f, 0.0f, 1.0f), 0.3f, vec3(-1.0f, 1.0f, -1.0f).normalize()));
		for (unsigned int i = 0; i < 8; i++)
		{
			ForwardPoint::getInstance().addPointLight(m_pointLights[i]);
		}
		ForwardSpot::getInstance().addSpotLight(m_spotLight);
		
		Scene *scene = new Scene(mat4::perspective(70.0f, 1000.0 / 800.0f, 0.01f, 1000.0f), new ForwardRenderer3D());
		scene->add(plane);
		scene->add(plane2);
		addScene(scene);
	}
	
	virtual void update(double delta) override
	{
		IGame::update(delta);
		m_temp += 0.025f;
		const float sinTemp = sinf(m_temp) * 7.0f;
		const float cosTemp = cosf(m_temp) * 7.0f;
		
		for (unsigned int i = 0; i < 8; i++)
		{
			if (i % 2 == 0) m_pointLights[i]->getPos().z = sinTemp;
			else			m_pointLights[i]->getPos().z = cosTemp;
		}
		
		m_spotLight->setPos(m_camera->getTransform().getPos());
		m_spotLight->setDirection(m_camera->getTransform().getRot().getBack());
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