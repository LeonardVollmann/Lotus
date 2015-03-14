#include "vertexarray.h"

namespace lotus { namespace graphics {
    
    VertexArray::VertexArray()
    {}
    
    VertexArray::VertexArray(GLfloat *vertices, GLsizei vcount) :
        m_vertices(vertices),
        m_vcount(vcount)
    {
        compile(vertices, vcount);
    }
    
    VertexArray::~VertexArray()
    {}
    
    void VertexArray::bind()
    {
        glBindVertexArray(m_vao);
    }
    
    void VertexArray::unbind()
    {
        glBindVertexArray(0);
    }
    
    void VertexArray::compile(GLfloat *vertices, GLsizei vcount)
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vcount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
} }