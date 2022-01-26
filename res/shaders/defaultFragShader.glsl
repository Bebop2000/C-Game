#version 330 core

in vec2 texCoords;
out vec4 colour;

uniform sampler2D image;

void main()
{
	colour = texture(image, texCoords);
	//if (colour.a < 0.1)
	//	discard;
}
