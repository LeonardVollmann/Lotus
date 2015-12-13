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
#include <core/entity/entity.hpp>
#include <core/entity/scenegraph.hpp>
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
#include <graphics/renderers/simplerenderer.hpp>
#include <graphics/renderers/forwardrenderer.hpp>
#include <graphics/renderers/waterrenderer.hpp>
#include <components/renderablecomponent.hpp>
#include <components/freemove.hpp>
#include <components/freelook.hpp>
#include <components/watercomponent.hpp>
#include <maths/maths.hpp>

using namespace lotus;
using namespace lotus::maths;
using namespace lotus::graphics;

class TestGame : public IGame
{
private:
	SpotLight *m_spotLight;
	PointLight *m_pointLights[8];
	Entity *m_monkey1;
	WaterComponent *water;
	WaterRenderer *waterRenderer;
	float m_temp = 0.0f;

public:
	TestGame()
	: IGame()
	, m_spotLight(new SpotLight(vec3f(1.0f, 1.0f, 1.0f),
	                            3.0f,
	                            Attenuation(0.0f, 0.0f, 1.0f),
	                            vec3f(0.0f, 0.0f, -6.0f),
	                            getForward(Transform().getRot()),
	                            0.7f))
	, m_pointLights{
	      new PointLight(vec3f(1.0f, 1.0f, 1.0f),
	                     0.5f,
	                     Attenuation(0.0f, 0.0f, 1.0f),
	                     vec3f(-7.0f, 0.0f, 0.0f)),
	      new PointLight(vec3f(1.0f, 0.0f, 0.0f),
	                     0.5f,
	                     Attenuation(0.0f, 0.0f, 1.0f),
	                     vec3f(-5.0f, 0.0f, 0.0f)),
	      new PointLight(vec3f(0.0f, 1.0f, 0.0f),
	                     0.5f,
	                     Attenuation(0.0f, 0.0f, 1.0f),
	                     vec3f(-3.0f, 0.0f, 0.0f)),
	      new PointLight(vec3f(0.0f, 0.0f, 1.0f),
	                     0.5f,
	                     Attenuation(0.0f, 0.0f, 1.0f),
	                     vec3f(-1.0f, 0.0f, 0.0f)),
	      new PointLight(vec3f(1.0f, 1.0f, 0.0f),
	                     0.5f,
	                     Attenuation(0.0f, 0.0f, 1.0f),
	                     vec3f(1.0f, 0.0f, 0.0f)),
	      new PointLight(vec3f(0.0f, 1.0f, 1.0f),
	                     0.5f,
	                     Attenuation(0.0f, 0.0f, 1.0f),
	                     vec3f(3.0f, 0.0f, 0.0f)),
	      new PointLight(vec3f(1.0f, 0.0f, 1.0f),
	                     0.5f,
	                     Attenuation(0.0f, 0.0f, 1.0f),
	                     vec3f(5.0f, 0.0f, 0.0f)),
	      new PointLight(vec3f(1.0f, 1.0f, 1.0f),
	                     0.5f,
	                     Attenuation(0.0f, 0.0f, 1.0f),
	                     vec3f(7.0f, 0.0f, 0.0f)),
	  }
	{
	}

	virtual ~TestGame() {}
	virtual void tick() override {}

	virtual void init() override
	{
		// glfwSwapInterval(0);
		//		Input::setMouseLocked(true);

		IndexedModel model;
		const float size = 10.0f;
		model.addPosition(vec3f(-size, size, 0));
		model.addPosition(vec3f(-size, -size, 0));
		model.addPosition(vec3f(size, -size, 0));
		model.addPosition(vec3f(size, size, 0));
		model.addTexCoord(vec2f(0, 3));
		model.addTexCoord(vec2f(0, 0));
		model.addTexCoord(vec2f(3, 0));
		model.addTexCoord(vec2f(3, 3));
		model.addFace(0, 1, 2);
		model.addFace(2, 3, 0);
		model.finalize();

		Material *material = new Material(new Texture("bricks.png"),
		                                  vec4f(),
		                                  2.0f,
		                                  32.0f,
		                                  new Texture("bricks_normal.png"),
		                                  new Texture("bricks_disp.png"),
		                                  0.04f);
		Material *material2 = new Material(new Texture("bricks2.png"),
		                                   vec4f(),
		                                   2.0f,
		                                   32.0f,
		                                   new Texture("bricks2_normal.png"),
		                                   new Texture("bricks2_disp.png"),
		                                   0.04f,
		                                   -1.0f);
		Material *material3 = new Material(new Texture("white.png"),
		                                   vec4f(),
		                                   0.0f,
		                                   0.0f,
		                                   new Texture("default_normal.png"),
		                                   new Texture("default_disp.png"),
		                                   0.0f,
		                                   0.0f);

		Entity *plane  = new Entity();
		Entity *plane2 = new Entity();
		m_monkey1 = new Entity();
		plane->getTransform().rotate(vec3f(1.0f, 0.0f, 0.0f), -3.14159f / 2.0f);
		plane2->getTransform().rotate(vec3f(1.0f, 0.0f, 0.0f), -3.14159f / 2.0f);
		plane2->getTransform().translate(vec3f(5.0f, 2.0f, 5.0f));
		plane2->getTransform().scale(vec3f(0.3f, 0.3f, 0.3f));
		m_monkey1->getTransform().translate(vec3f(0.0f, 3.0f, 0.0f));

		m_camera->addComponent<FreeMove>(10.0f);
		m_camera->addComponent<FreeLook>(5.0f);
		m_camera->bind();

		plane->addComponent<RenderableComponent>(new Renderable(model), material);
		plane2->addComponent<RenderableComponent>(new Renderable(model), material2);
		m_monkey1->addComponent<RenderableComponent>(new Renderable(IndexedModel("monkey")),
		                                             material3);

		ForwardRenderer *renderer = new ForwardRenderer();
		renderer->setAmbientLight(vec3f(0.1f));
		renderer->addDirectionalLight(new DirectionalLight(
		    vec3f(1.0f, 0.0f, 0.0f), 0.4f, normalize(vec3f(1.0f, 1.0f, 1.0f))));
		renderer->addDirectionalLight(new DirectionalLight(
		    vec3f(0.0f, 0.0f, 1.0f), 0.4f, normalize(vec3f(-1.0f, 1.0f, -1.0f))));
		for (unsigned int i = 0; i < 8; i++)
		{
			renderer->addPointLight(m_pointLights[i]);
		}
		renderer->addSpotLight(m_spotLight);

		Scene *scene = new Scene(perspective(70.0f, 1000.0f / 800.0f, 0.01f, 1000.0f), renderer);
		scene->add(plane);
		scene->add(plane2);
		scene->add(m_monkey1);

		addScene(scene);

		// EntityWorld w;
		// SceneGraph sg(16);
		// EntityID e0 = w.create();
		// EntityID e1 = w.create();
		// EntityID e2 = w.create();
		// EntityID e3 = w.create();
		// sg.create(e0, mat4f(1.0f));
		// sg.create(e1, mat4f(1.0f));
		// sg.create(e2, mat4f(1.0f));
		// sg.create(e3, mat4f(1.0f));
		// sg.link(sg.getInstanceID(e1), sg.getInstanceID(e0));
		// sg.link(sg.getInstanceID(e2), sg.getInstanceID(e0));
		// sg.link(sg.getInstanceID(e3), sg.getInstanceID(e1));
		// sg.printInstanceData();

		water         = new WaterComponent(maths::vec3f(0, 1, 0), maths::vec2f(10.0f));
		waterRenderer = new WaterRenderer();
	}

	virtual void shutdown() override {}

	virtual void update(double delta) override
	{
		IGame::update(delta);
		m_temp += 0.02f;
		const float sinTemp = sinf(m_temp);
		const float cosTemp = cosf(m_temp);

		for (unsigned int i = 0; i < 8; i++)
		{
			if (i % 2 == 0)
				m_pointLights[i]->getPos().z = sinTemp * 7.0f;
			else
				m_pointLights[i]->getPos().z = cosTemp * 7.0f;
		}

		m_spotLight->setPos(m_camera->getTransform().getPos());
		m_spotLight->setDirection(getForward(m_camera->getTransform().getRot()));

		m_monkey1->getTransform().rotate(vec3f(0.0f, 1.0f, 0.0f), 0.01f);
	}

	virtual void render() override
	{
		IGame::render();
		water->render(waterRenderer);
		waterRenderer->flush();
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
