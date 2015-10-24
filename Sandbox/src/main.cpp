#include <iostream>
#include <cmath>
#include <vector>

#include <core/igame.hpp>
#include <core/engine.hpp>
#include <core/input.hpp>
#include <core/time.hpp>
#include <core/transform.hpp>
#include <core/entity.hpp>
#include <core/maths.hpp>
#include <core/stringfunc.hpp>
#include <graphics/window.hpp>
#include <graphics/lighting.hpp>
#include <graphics/camera.hpp>
#include <graphics/vertex.hpp>
#include <graphics/renderable.hpp>
#include <graphics/texture.hpp>
#include <graphics/material.hpp>
#include <graphics/indexedmodel.hpp>
#include <graphics/scene.hpp>
#include <graphics/shader.hpp>
#include <graphics/renderers/simplerenderer.hpp>
#include <graphics/renderers/forwardrenderer3d.hpp>
#include <graphics/renderers/spriterenderer2d.hpp>
#include <components/renderablecomponent.hpp>
#include <components/freemove.hpp>
#include <components/freelook.hpp>
#include <components/spritecomponent.hpp>

using namespace lotus;
using namespace lotus::maths;
using namespace lotus::graphics;

typedef Renderable<Vertex2D> Renderable2D;
typedef Renderable<Vertex3D> Renderable3D;
typedef RenderableComponent<Renderable2D> RenderableComponent2D;
typedef RenderableComponent<Renderable3D> RenderableComponent3D;

class TestGame : public IGame
{
private:
	SpotLight	*m_spotLight;
	PointLight	*m_pointLights[8];
	Entity 		*m_monkey1;
	Entity		*sprites;
	float m_temp = 0.0f;
public:
	TestGame() :
		IGame(),
		m_spotLight(new SpotLight(Vector3f(1.0f, 1.0f, 1.0f), 3.0f, Attenuation(0.0f, 0.0f, 1.0f), Vector3f(0.0f, 0.0f, -6.0f), getForward(Transform().getRot()), 0.7f)),
		m_pointLights
		{
			new PointLight(Vector3f(1.0f, 1.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), Vector3f(-7.0f, 0.0f, 0.0f)),
			new PointLight(Vector3f(1.0f, 0.0f, 0.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), Vector3f(-5.0f, 0.0f, 0.0f)),
			new PointLight(Vector3f(0.0f, 1.0f, 0.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), Vector3f(-3.0f, 0.0f, 0.0f)),
			new PointLight(Vector3f(0.0f, 0.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), Vector3f(-1.0f, 0.0f, 0.0f)),
			new PointLight(Vector3f(1.0f, 1.0f, 0.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), Vector3f( 1.0f, 0.0f, 0.0f)),
			new PointLight(Vector3f(0.0f, 1.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), Vector3f( 3.0f, 0.0f, 0.0f)),
			new PointLight(Vector3f(1.0f, 0.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), Vector3f( 5.0f, 0.0f, 0.0f)),
			new PointLight(Vector3f(1.0f, 1.0f, 1.0f), 0.5f, Attenuation(0.0f, 0.0f, 1.0f), Vector3f( 7.0f, 0.0f, 0.0f)),
		}
	{}

	virtual ~TestGame() {}
	virtual void tick() override {}

	virtual void init() override
	{
		// glfwSwapInterval(0);
//		Input::setMouseLocked(true);

		IndexedModel model;
		const float size = 10.0f;
		model.addPosition(Vector3f(-size, size, 0));
		model.addPosition(Vector3f(-size, -size, 0));
		model.addPosition(Vector3f(size, -size, 0));
		model.addPosition(Vector3f(size, size, 0));
		model.addTexCoord(Vector2f(0, 3));
		model.addTexCoord(Vector2f(0, 0));
		model.addTexCoord(Vector2f(3, 0));
		model.addTexCoord(Vector2f(3, 3));
		model.addFace(0, 1, 2);
		model.addFace(2, 3, 0);
		model.finalize();

		Material *material = new Material(new Texture("bricks.png"), Vector4f(), 2.0f, 32.0f, new Texture("bricks_normal.png"), new Texture("bricks_disp.png"), 0.04f);
		Material *material2 = new Material(new Texture("bricks2.png"), Vector4f(), 2.0f, 32.0f, new Texture("bricks2_normal.png"), new Texture("bricks2_disp.png"), 0.04f, -1.0f);
		Material *material3 = new Material(new Texture("white.png"), Vector4f(), 0.0f, 0.0f, new Texture("default_normal.png"), new Texture("default_disp.png"), 0.0f, 0.0f);

		Entity *plane = new Entity();
		Entity *plane2 = new Entity();
		m_monkey1 = new Entity();
		plane->getTransform().rotate(Vector3f(1.0f, 0.0f, 0.0f), -3.14159f / 2.0f);
		plane2->getTransform().rotate(Vector3f(1.0f, 0.0f, 0.0f), -3.14159f / 2.0f);
		plane2->getTransform().translate(Vector3f(5.0f, 2.0f, 5.0f));
		plane2->getTransform().scale(Vector3f(0.3f, 0.3f, 0.3f));
		m_monkey1->getTransform().translate(Vector3f(0.0f, 3.0f, 0.0f));

		m_camera->addComponent<FreeMove>(10.0f);
		m_camera->addComponent<FreeLook>(5.0f);
		m_camera->bind();

		plane->addComponent<RenderableComponent3D>(new Renderable3D(model), material);
		plane2->addComponent<RenderableComponent3D>(new Renderable3D(model), material2);
		m_monkey1->addComponent<RenderableComponent3D>(new Renderable3D(IndexedModel("monkey")), material3);

		ForwardRenderer3D *renderer = new ForwardRenderer3D();
		renderer->setAmbientLight(Vector3f(0.1f));
		renderer->addDirectionalLight(new DirectionalLight(Vector3f(1.0f, 0.0f, 0.0f), 0.4f, normalize(Vector3f(1.0f, 1.0f, 1.0f))));
		renderer->addDirectionalLight(new DirectionalLight(Vector3f(0.0f, 0.0f, 1.0f), 0.4f, normalize(Vector3f(-1.0f, 1.0f, -1.0f))));
		for (unsigned int i = 0; i < 8; i++)
		{
			renderer->addPointLight(m_pointLights[i]);
		}
		renderer->addSpotLight(m_spotLight);

		Scene *scene = new Scene(perspective(70.0f, 1000.0f / 800.0f, 0.01f, 1000.0f), renderer);
		scene->add(plane);
		scene->add(plane2);
		scene->add(m_monkey1);

		//		Entity *sprite = new Entity();
		//		sprite->getTransform().translate(vec3(0.0f, 0.0f, 0.1f));
		//		sprite->addComponent(new SpriteComponent());

		SpriteRenderer2D *spriteRenderer = new SpriteRenderer2D();
		Scene *scene2 = new Scene(orthographic(-1000.0f / 800.0f, 1000.0f / 800.0f, -1.0f, 1.0f, -1.0f, 1.0f), spriteRenderer);
		//		scene2->add(sprite);

		sprites = new Entity();
		const unsigned int n = 75;
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < n; j++)
			{
				Entity *sprite = new Entity();
				sprite->getTransform().scale(Vector3f(0.01f, 0.01f, 1.0f));
				sprite->getTransform().translate(Vector3f(j * 0.02f - (float(n) / 100.0f), i * 0.02f - (float(n) / 100.0f), 0.0f));
				sprite->addComponent(new SpriteComponent());

				sprites->addChild(sprite);
			}
		}
		scene2->add(sprites);

		addScene(scene);
		addScene(scene2);
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
			if (i % 2 == 0) m_pointLights[i]->getPos().z = sinTemp * 7.0f;
			else			m_pointLights[i]->getPos().z = cosTemp * 7.0f;
		}

		m_spotLight->setPos(m_camera->getTransform().getPos());
		m_spotLight->setDirection(getForward(m_camera->getTransform().getRot()));

		m_monkey1->getTransform().rotate(Vector3f(0.0f, 1.0f, 0.0f), 0.01f);

		sprites->getTransform().rotate(Vector3f(0.0f, 0.0f, 1.0f), 0.001f);
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
