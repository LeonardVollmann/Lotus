#ifndef LOTUS_RECTANGLE_H
#define LOTUS_RECTANGLE_H

#include "primitive.h"

namespace lotus { namespace graphics {
   
    class Rectangle : public Primitive
    {
    private:
        float m_width, m_height;
    public:
        Rectangle();
        Rectangle(float width, float height);
        
        void setWidth(float width);
        void setHeight(float height);
        
        inline float getWidth() { return m_width; }
        inline float getHeight() { return m_height; }
    private:
        virtual void compile() final;
    };
    
} }

#endif