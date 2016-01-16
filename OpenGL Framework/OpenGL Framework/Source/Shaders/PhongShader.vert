#version 440 core
precision highp float;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoords;

out vec3 wsPosition;
out vec3 wsNormal;
out vec2 Texcoords;

uniform mat4 MVP;

void main(){
	gl_Position = vec4(inPos, 1.f);
	wsPosition	= inPos;
	wsNormal	= inNormal;
	Texcoords	= inTexCoords;
}
