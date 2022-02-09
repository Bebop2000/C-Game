#version 330 core

in vec2 texCoords;
out vec4 colour;

uniform sampler2D image;

void main()
{
	float ambientStrength = 0.8;
	colour = texture(image, texCoords) * ambientStrength;
	if (colour.a < 0.1)
		discard;
}
