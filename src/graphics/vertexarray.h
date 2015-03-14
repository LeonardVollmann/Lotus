#ifndef LOTUS_VERTEXARRAY_H
#define LOTUS_VERTEXARRAY_H

#include <GL/glew.h>

namespace lotus { namespace graphics {
    
    class VertexArray
    {
    private:
        GLsizei m_vcount;
        GLuint m_vao, m_vbo;
        const GLfloat *m_vertices;
    public:
        VertexArray();
        VertexArray(GLfloat *vertices, GLsizei vcount);
        virtual ~VertexArray();
        
        void bind();
        void unbind();
    private:
        void compile(GLfloat *vertices, GLsizei vcount);
    };
    
} }

#endif