#version 330 core

in DATA
{
	vec2 texCoord;
	vec3 worldPos;
	mat3 tbn_matrix;
} fs_in;

out vec4 fragColor;

uniform vec4 baseColor;
uniform float specularIntensity;
uniform float specularPower;
uniform vec3 cameraPos;
uniform float dispMapScale;
uniform float dispMapBias;

uniform sampler2D diffuse;
uniform sampler2D normalMap;
uniform sampler2D dispMap;

#include lighting.glsl