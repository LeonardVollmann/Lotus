#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec2 vertex_texCoord;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec3 vertex_tangent;

uniform mat4 mvp_matrix;
uniform mat4 ml_matrix;

out DATA
{
	vec2 texCoord;
	vec3 worldPos;
	mat3 tbn_matrix;
} vs_out;

void main()
{
	gl_Position = mvp_matrix * vec4(vertex_pos, 1.0);
	vs_out.texCoord = vertex_texCoord;
	vs_out.worldPos = (ml_matrix * vec4(vertex_pos, 1.0)).xyz;
	
	vec3 normal = normalize((ml_matrix * vec4(vertex_normal, 0.0)).xyz);
	vec3 tangent = normalize((ml_matrix * vec4(vertex_tangent, 0.0)).xyz);
	
	tangent = normalize(tangent - dot(tangent, normal) * normal);
	
	vec3 biTangent = normalize(cross(tangent, normal));
	
	vs_out.tbn_matrix = mat3(tangent, biTangent, normal);
}