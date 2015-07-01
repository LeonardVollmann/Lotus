#version 330 core

in DATA
{
	vec2 texCoord;
	vec3 worldPos;
	mat3 tbn_matrix;
} fs_in;

out vec4 fragColor;

uniform vec4 material_color;
uniform float material_specularIntensity;
uniform float material_specularPower;
uniform float material_dispMapScale;
uniform float material_dispMapBias;
uniform vec3 camera_pos;

uniform sampler2D material_diffuse;
uniform sampler2D material_normalMap;
uniform sampler2D material_dispMap;

#include lighting.glsl