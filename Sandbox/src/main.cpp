#include <iostream>
#include <cmath>
#include <vector>

#include <core/igame.hpp>
#include <core/engine.hpp>
#include <core/input.hpp>
#include <core/time.hpp>
#include <core/transform.hpp>
#include <core/entity.hpp>
#include <core/stringfunc.hpp>
#include <memory/memory.hpp>
#include <maths/maths.hpp>
#include <graphics/window.hpp>
#include <graphics/lighting.hpp>
#include <graphics/camera.hpp>
#include <graphics/vertex.hpp>
#include <graphics/renderable.hpp>
#include <graphics/texture.hpp>
#include <graphics/material.hpp>
#include <graphics/indexedmodel.hpp>
#include <graphics/scene.hpp>
#include <graphics/shaders/shader.hpp>
#include <graphics/shaders/shaderfactory.hpp>
#include <graphics/renderers/simplerenderer.hpp>
#include <graphics/renderers/forwardrenderer3d.hpp>
#include <graphics/renderers/batchrenderer2d.hpp>
#include <components/renderablecomponent.hpp>
#include <components/freemove.hpp>
#include <components/freelook.hpp>
#include <components/spritecomponent.hpp>

using namespace lotus;
using namespace lotus::maths;
using namespace lotus::graphics;
using namespace lotus::memory;
using namespace lotus::internal;

typedef Renderable<Vertex2D> Renderable2D;
typedef Renderable<Vertex3D> Renderable3D;
typedef RenderableComponent<Renderable2D> RenderableComponent2D;
typedef RenderableComponent<Renderable3D> RenderableComponent3D;

class TestGame : public IGame
{
private:
	SpotLight	*m_spotLight;
	PointLight	*m_pointLights[8];
	float m_temp = 0.0f;
public:
	TestGame() :
		IGame(),
		m_spotLight(new SpotLight(vec3(1.0f, 1.0f, 1.0f), 3.0f, Attenuation(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -6.0f), vec3(Transform().getRot().getForward()), 0.7f)),
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

		std::string s = "   Hello,  World!  ";
		std::vector<std::string> tokens = tokenize(s, ' ');
		for (auto it = tokens.begin(); it < tokens.end(); it++) std::cout << *it << std::endl;
		std::cout << removeWhiteSpace(s) << std::endl;
		std::cout << startsWith(s, "Hello,") << std::endl;
		std::cout << endsWith(s, "World!") << std::endl;
		std::cout << join(tokens, " ") << std::endl;
		std::cout << toUpperCase(s) << ", " << toLowerCase(s) << std::endl;
		std::cout << contains(s, "llo,w") << std::endl;

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
		Material *material3 = new Material(new Texture("white.png"), vec4::ZERO, 0.0f, 0.0f, new Texture("default_normal.png"), new Texture("default_disp.png"), 0.0f, 0.0f);

		Entity *plane = new Entity();
		Entity *plane2 = new Entity();
		Entity *monkey = new Entity();
		plane->getTransform().rotate(-MATH_PI / 2.0f, vec3(1.0f, 0.0f, 0.0f));
		plane2->getTransform().rotate(-MATH_PI / 2.0f, vec3(1.0f, 0.0f, 0.0f));
		plane2->getTransform().translate(vec3(5.0f, 2.0f, 5.0f));
		plane2->getTransform().scale(vec3(0.3f, 0.3f, 0.3f));
		monkey->getTransform().translate(vec3(0.0f, 3.0f, 0.0f));

		m_camera->addComponent<FreeMove>(10.0f);
		m_camera->addComponent<FreeLook>(5.0f);
		m_camera->bind();

		plane->addComponent<RenderableComponent3D>(new Renderable3D(model), material);
		plane2->addComponent<RenderableComponent3D>(new Renderable3D(model), material2);
		monkey->addComponent<RenderableComponent3D>(new Renderable3D(IndexedModel("monkey").finalize()), material3);

		ForwardRenderer3D *renderer = new ForwardRenderer3D();
		renderer->setAmbientLight(vec3(0.1f));
		renderer->addDirectionalLight(new DirectionalLight(vec3(1.0f, 0.0f, 0.0f), 0.4f, vec3(1.0f, 1.0f, 1.0f).normalize()));
		renderer->addDirectionalLight(new DirectionalLight(vec3(0.0f, 0.0f, 1.0f), 0.4f, vec3(-1.0f, 1.0f, -1.0f).normalize()));
		for (unsigned int i = 0; i < 8; i++)
		{
			renderer->addPointLight(m_pointLights[i]);
		}
		renderer->addSpotLight(m_spotLight);

		Scene *scene = new Scene(mat4::perspective(70.0f, 1000.0 / 800.0f, 0.01f, 1000.0f), renderer);
		scene->add(plane);
		scene->add(plane2);
		scene->add(monkey);
		addScene(scene);
	}

	virtual void shutdown() override {}

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
