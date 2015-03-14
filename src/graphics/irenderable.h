#ifndef LOTUS_I_RENDERABLE_H
#define LOTUS_I_RENDERABLE_H

namespace lotus { namespace graphics {
    
    class IRenderable
    {
    public:
        virtual void render() const = 0;
    };
    
} }

#endif