#version 440 core
precision highp float;

in vec3 wsPosition;
in vec3 wsNormal;
in vec2 TexCoords;

out vec4 Color;

void main(){
	Color = vec4(wsPosition, 1.f);
}
