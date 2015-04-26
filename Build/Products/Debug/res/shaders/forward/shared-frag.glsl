#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 worldPos;

out vec4 fragColor;

uniform vec3 cameraPos;

uniform sampler2D diffuse;
uniform vec4 baseColor;
uniform float specularIntensity;
uniform float specularPower;

#include lighting.glsl