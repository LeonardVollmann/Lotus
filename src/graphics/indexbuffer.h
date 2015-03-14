#ifndef LOTUS_INDEXBUFFER_H
#define LOTUS_INDEXBUFFER_H

#include "i_renderable.h"

#include <GL/glew.h>

namespace lotus { namespace graphics {
   
    class IndexBuffer : public IRenderable
    {
    private:
        GLuint m_ibo;
        GLushort *m_indices;
        GLsizei m_icount;
    public:
        IndexBuffer();
        IndexBuffer(GLushort *indices, GLsizei icount);
        virtual ~IndexBuffer();
        
        void render();
        void bind();
        void unbind();
    private:
        void compile(GLushort *indices, GLsizei icount);
    };
    
} }

#endif