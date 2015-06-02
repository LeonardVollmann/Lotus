#ifndef LOTUS_PHONG_RENDERER_3D_HPP_INCLUDED
#define LOTUS_PHONG_RENDERER_3D_HPP_INCLUDED

#include "lotus_simplerenderer3d.hpp"

class PhongRenderer3D : public SimpleRenderer3D
{
public:
	virtual void flush() override;
};

#endif