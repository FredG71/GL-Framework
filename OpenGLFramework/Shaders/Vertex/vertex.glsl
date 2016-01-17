#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoords;

uniform mat4 MVP;

out vec3 vPos;
out vec3 vNormal;
out vec2 vTexCoords;

void main()
{
	gl_Position = MVP * vec4(position.rgb, 1);
	vPos = position;
	vNormal = normal;
	vTexCoords = texcoords;
}