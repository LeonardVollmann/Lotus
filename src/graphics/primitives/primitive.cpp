#include "primitive.h"

namespace lotus { namespace graphics {
    
    Primitive::~Primitive()
    {
        delete m_vao;
        delete m_ibo;
    }
    
    void Primitive::render() const
    {
        m_vao->bind();
        m_ibo->render();
        m_vao->unbind();
    }
    
} }