#version 330 core

layout (location=0) in vec3 vertex;
layout (location=1) in vec2 UV;

out vec2 texCoords;

uniform int instanced;
uniform vec2 offsets[100];
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 projectionTimesView;

void main()
{
	if(instanced == 0)
	{
		texCoords = UV;
		gl_Position = projectionTimesView * model * vec4(vertex, 1.0);
		//gl_Position = projectionTimesView * vec4(vertex, 1.0);
	}
	if(instanced == 1)
	{
		texCoords = UV;
		gl_Position = projectionTimesView * model *
	}


}