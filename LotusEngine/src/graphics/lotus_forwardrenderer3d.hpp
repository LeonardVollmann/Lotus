#ifndef LOTUS_FORWARD_RENDERER_3D_HPP_INCLUDED
#define LOTUS_FORWARD_RENDERER_3D_HPP_INCLUDED

#include "lotus_simplerenderer3d.hpp"

class ForwardRenderer3D : public SimpleRenderer3D
{
public:
	virtual void flush() override;
};

#endif