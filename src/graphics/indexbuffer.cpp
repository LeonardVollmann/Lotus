#include "indexbuffer.h"

namespace lotus { namespace graphics {

    IndexBuffer::IndexBuffer()
    {}
    
    IndexBuffer::IndexBuffer(GLushort *indices, GLsizei icount) :
        m_indices(indices),
        m_icount(icount)
    {
        compile(indices, icount);
    }
    
    IndexBuffer::~IndexBuffer()
    {}
    
    void IndexBuffer::render()
    {
        bind();
        glDrawElements(GL_TRIANGLES, m_icount, GL_UNSIGNED_SHORT, nullptr);
        unbind();
    }
    
    void IndexBuffer::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    }
    
    void IndexBuffer::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    void IndexBuffer::compile(GLushort *indices, GLsizei icount)
    {
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(GLushort), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
} }