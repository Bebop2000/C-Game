#pragma once
typedef struct
{
	unsigned int ID;
	unsigned int width, height;
	unsigned int internalFormat; // format of texture object
	unsigned int imageFormat; // format of loaded image
	// texture configuration
	//possibly set different configurations for each texture as needed in the future
	//for now all I need is the default

	unsigned int Wrap_S; // wrapping mode on S axis
	unsigned int Wrap_T; // wrapping mode on T axis
	unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
	unsigned int Filter_Max;
} Texture2D;

void loadTextureFromFile(Texture2D* texture, const char* file, int ch);
