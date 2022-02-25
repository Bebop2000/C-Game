#include "core.h"
#include "texture.h"
#include "../vendor/stb_image.h"


// channels refers to the number of channels in the image format
// jpg (rgb) = 3 channels
// png (rgba) = 4 channels
void loadTextureFromFile(Texture* texture, const char* file) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, STBI_rgb_alpha);
	if(!data) {
		printf("Error loading texture %s\n", file);
		stbi_image_free(data);
	}
	else{
		texture->width = width;
		texture->height = height;
		glGenTextures(1, &texture->ID);
		glBindTexture(GL_TEXTURE_2D, texture->ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
}
