#version 330 core

out vec4 fragmentDepth;

void main()
{
	fragmentDepth = vec4(gl_FragCoord.z);
}
