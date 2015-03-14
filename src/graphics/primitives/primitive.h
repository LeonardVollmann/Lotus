#ifndef LOTUS_PRIMITIVE_H
#define LOTUS_PRIMITIVE_H

#include "../vertexarray.h"
#include "../indexbuffer.h"
#include "../irenderable.h"

namespace lotus { namespace graphics {
    
    class Primitive : IRenderable
    {
    protected:
        VertexArray *m_vao;
        IndexBuffer *m_ibo;
    public:
        virtual ~Primitive();
        
        virtual void render() const final;
    protected:
        virtual void compile() = 0;
    };
    
} }

#endif