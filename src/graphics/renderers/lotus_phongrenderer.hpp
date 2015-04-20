#ifndef LOTUS_PHONG_RENDERER_HPP_INCLUDED
#define LOTUS_PHONG_RENDERER_HPP_INCLUDED

#include "lotus_simplerenderer.hpp"

class PhongRenderer : public SimpleRenderer
{
public:
	virtual void render() override;
};

#endif