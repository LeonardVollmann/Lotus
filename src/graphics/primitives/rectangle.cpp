#include "rectangle.h"

namespace lotus { namespace graphics {

    Rectangle::Rectangle() :
        m_width(1.0f),
        m_height(1.0f)
    {
        compile();
    }
    
    Rectangle::Rectangle(float width, float height) :
        m_width(width),
        m_height(height)
    {
        compile();
    }
    
    void Rectangle::setWidth(float width)
    {
        m_width = width;
        compile();
    }
    
    void Rectangle::setHeight(float height)
    {
        m_height = height;
    }
    
    void Rectangle::compile()
    {
        float xCoord = m_width / 2.0f;
        float yCoord = m_height / 2.0f;
        
        GLfloat vertices[]  = {
            -xCoord, -yCoord, 0.0f,
            -xCoord,  yCoord, 0.0f,
             xCoord,  yCoord, 0.0f,
             xCoord, -yCoord, 0.0f
        };
        
        GLushort indices[] = {
            0, 1, 2,
            0, 2, 3
        };
        
        m_vao = new VertexArray(vertices, 4);
        m_ibo = new IndexBuffer(indices, 6);
    }
    
} }