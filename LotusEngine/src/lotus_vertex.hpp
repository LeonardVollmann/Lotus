#ifndef LOTUS_VERTEX_HPP_INCLUDED
#define LOTUS_VERTEX_HPP_INCLUDED

#include "lotus_vec3.hpp"
#include "lotus_vec2.hpp"

struct Vertex2D
{
	vec3 position;
	vec2 texCoord;
	
	Vertex2D(const vec3 &position, const vec2 &texCoord) :
		position(position),
		texCoord(texCoord) {}
};

struct Vertex3D
{
	vec3 position;
	vec2 texCoord;
	vec3 normal;
	vec3 tangent;
	
	Vertex3D(const vec3 &position, const vec2 &texCoord, const vec3 &normal, const vec3 &tangent) :
		position(position),
		texCoord(texCoord),
		normal(normal),
		tangent(tangent) {}
};

#endif