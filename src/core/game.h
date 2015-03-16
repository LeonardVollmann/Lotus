#ifndef LOTUS_GAME_H
#define LOTUS_GAME_H

namespace lotus {

    class Engine;
    
    class Game
    {
    protected:
        Engine *m_engine;
    public:
        virtual void update(float delta) = 0;
        virtual void render() = 0;
        
        inline void setEngine(Engine *engine) { m_engine = engine; }
    };
    
}

#endif