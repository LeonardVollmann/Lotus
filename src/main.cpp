#include "core/engine.h"
#include "core/game.h"
#include "maths/math.h"
#include "graphics/primitives/rectangle.h"
#include "graphics/shader.h"

#include <iostream>

class TestGame : public lotus::Game
{
private:
    lotus::graphics::Rectangle m_rect;
    lotus::graphics::Shader m_shader;
public:
    TestGame() :
        m_shader("shader"),
        m_rect(1.0f, 1.0f)
    {
        m_shader.addVertexShader().addFragmentShader().compile();
    }
    
    virtual void update(float delta) override
    {
        
    }
    
    virtual void render() override
    {
        m_shader.bind();
        m_rect.render();
        m_shader.unbind();
    }
};

int main()
{
    lotus::Engine engine(60, 600, 400, "Lotus Engine");
    TestGame *game = new TestGame();
    engine.setGame(game);
    engine.start();
    
    delete game;
    
    return 0;
}