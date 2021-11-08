#version 330 core

in vec2 texCoords;
out vec4 colour;

uniform sampler2D image;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main()
{
	colour = texture(image, texCoords);
	if (colour.a < 0.1)
		discard;
}
