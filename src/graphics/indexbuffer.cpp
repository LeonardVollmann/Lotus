#include "indexbuffer.h"

namespace lotus { namespace graphics {

    IndexBuffer::IndexBuffer()
    {}
    
    IndexBuffer::IndexBuffer(GLushort *indices, GLsizei icount) :
        m_indices(indices),
        m_icount(icount)
    {
        compile();
    }
    
    IndexBuffer::~IndexBuffer()
    {}
    
    void IndexBuffer::render() const
    {
        bind();
        glDrawElements(GL_TRIANGLES, m_icount, GL_UNSIGNED_SHORT, nullptr);
        unbind();
    }
    
    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    }
    
    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    void IndexBuffer::compile()
    {
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_icount * sizeof(GLushort), m_indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
} }