#ifndef LOTUS_INDEXBUFFER_H
#define LOTUS_INDEXBUFFER_H

#include "irenderable.h"

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
        
        virtual void render() const override;
        void bind() const;
        void unbind() const;
    private:
        void compile(GLushort *indices, GLsizei icount);
    };
    
} }

#endif