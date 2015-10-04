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
#include <graphics/shader.hpp>
#include <graphics/renderers/simplerenderer.hpp>
#include <graphics/renderers/forwardrenderer3d.hpp>
#include <graphics/renderers/spriterenderer2d.hpp>
#include <components/renderablecomponent.hpp>
#include <components/spritecomponent.hpp>
#include <components/freemove.hpp>
#include <components/freelook.hpp>

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
	Entity 		*m_monkey2;
	Entity 		*m_monkey3;
	Entity 		*m_monkey4;
	Entity 		*m_monkey5;
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
	virtual void tick() override {}

	virtual void init() override
	{
		// glfwSwapInterval(0);
//		Input::setMouseLocked(true);

		IndexedModel model;
		const float size = 10.0f;
		model.addPosition(vec3(-size, size, 0));
		model.addPosition(vec3(-size, -size, 0));
		model.addPosition(vec3(size, -size, 0));
		model.addPosition(vec3(size, size, 0));
		model.addTexCoord(vec2(0, 3));
		model.addTexCoord(vec2(0, 0));
		model.addTexCoord(vec2(3, 0));
		model.addTexCoord(vec2(3, 3));
		model.addFace(0, 1, 2);
		model.addFace(2, 3, 0);
		model.finalize();

		Material *material = new Material(new Texture("bricks.png"), vec4::ZERO, 2.0f, 32.0f, new Texture("bricks_normal.png"), new Texture("bricks_disp.png"), 0.04f);
		Material *material2 = new Material(new Texture("bricks2.png"), vec4::ZERO, 2.0f, 32.0f, new Texture("bricks2_normal.png"), new Texture("bricks2_disp.png"), 0.04f, -1.0f);
		Material *material3 = new Material(new Texture("white.png"), vec4::ZERO, 0.0f, 0.0f, new Texture("default_normal.png"), new Texture("default_disp.png"), 0.0f, 0.0f);

		Entity *plane = new Entity();
		Entity *plane2 = new Entity();
		m_monkey1 = new Entity();
		m_monkey2 = new Entity();
		m_monkey3 = new Entity();
		m_monkey4 = new Entity();
		m_monkey5 = new Entity();
		plane->getTransform().rotate(-MATH_PI / 2.0f, vec3(1.0f, 0.0f, 0.0f));
		plane2->getTransform().rotate(-MATH_PI / 2.0f, vec3(1.0f, 0.0f, 0.0f));
		plane2->getTransform().translate(vec3(5.0f, 2.0f, 5.0f));
		plane2->getTransform().scale(vec3(0.3f, 0.3f, 0.3f));
		m_monkey1->getTransform().translate(vec3(0.0f, 3.0f, 0.0f));
		m_monkey2->getTransform().scale(vec3(0.25f));
		m_monkey3->getTransform().scale(vec3(0.25f));
		m_monkey4->getTransform().scale(vec3(0.25f));
		m_monkey5->getTransform().scale(vec3(0.25f));

		m_monkey1->addChild(m_monkey2);
		m_monkey1->addChild(m_monkey3);
		// m_monkey1->addChild(m_monkey4);
		// m_monkey1->addChild(m_monkey5);

		m_camera->addComponent<FreeMove>(10.0f);
		m_camera->addComponent<FreeLook>(5.0f);
		m_camera->bind();

		plane->addComponent<RenderableComponent3D>(new Renderable3D(model), material);
		plane2->addComponent<RenderableComponent3D>(new Renderable3D(model), material2);
		m_monkey1->addComponent<RenderableComponent3D>(new Renderable3D(IndexedModel("monkey")), material3);
		m_monkey2->addComponent<RenderableComponent3D>(new Renderable3D(IndexedModel("monkey")), material3);
		m_monkey3->addComponent<RenderableComponent3D>(new Renderable3D(IndexedModel("monkey")), material3);
		// m_monkey4->addComponent<RenderableComponent3D>(new Renderable3D(IndexedModel("monkey")), material3);
		// m_monkey5->addComponent<RenderableComponent3D>(new Renderable3D(IndexedModel("monkey")), material3);

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
		scene->add(m_monkey1);
		
//		Entity *sprite = new Entity();
//		sprite->getTransform().translate(vec3(0.0f, 0.0f, 1.0f));
//		sprite->addComponent(new SpriteComponent());
		
		SpriteRenderer2D *spriteRenderer = new SpriteRenderer2D();
		Scene *scene2 = new Scene(mat4::perspective(70.0f, 1000.0 / 800.0f, 0.01f, 1000.0f), spriteRenderer);
//		scene2->add(sprite);
		
		const unsigned int n = 100;
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < n; j++)
			{
				Entity *sprite = new Entity();
				sprite->getTransform().translate(maths::vec3(j * 2, i * 2 + 10, 0));
				sprite->addComponent(new SpriteComponent());
				scene2->add(sprite);
			}
		}
		
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
		m_spotLight->setDirection(m_camera->getTransform().getRot().getBack());

		m_monkey1->getTransform().rotate(0.01f, vec3(0.0f, 1.0f, 0.0f));

		m_monkey2->getTransform().getPos().x = sinTemp * 2.0f;
		m_monkey2->getTransform().getPos().z = cosTemp * 2.0f;
		m_monkey3->getTransform().getPos().x = sinTemp * 2.0f;
		m_monkey3->getTransform().getPos().y = cosTemp * 2.0f;
		m_monkey4->getTransform().getPos().x = -sinTemp * 2.0f;
		m_monkey4->getTransform().getPos().z = -cosTemp * 2.0f;
		m_monkey5->getTransform().getPos().x = -sinTemp * 2.0f;
		m_monkey5->getTransform().getPos().y = -cosTemp * 2.0f;
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
