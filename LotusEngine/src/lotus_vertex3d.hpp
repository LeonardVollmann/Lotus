#ifndef LOTUS_VERTEX_3D_HPP_INCLUDED
#define LOTUS_VERTEX_3D_HPP_INCLUDED

#include "lotus_vec3.hpp"
#include "lotus_vec2.hpp"

struct Vertex3D
{
	vec3 position;
	vec2 texCoord;
	vec3 normal;
	vec3 tangent;
	
	Vertex3D(const vec3 &position, const vec2 &texCoord, const vec3 &normal, const vec3 &tangent)
	{
		this->position = position;
		this->texCoord = texCoord;
		this->normal = normal;
		this->tangent = tangent;
	}
};

#endif