#include "TextureLoader.h"

GLuint TextureLoader::getTexture(const char *pathTexture)
{
	GLuint texture;

	glGenTextures(1, &texture);
	
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int w, h;
	unsigned char *image = SOIL_load_image(pathTexture, &w, &h,0,SOIL_LOAD_RGB);

	if (!image)
	{
		std::cout << "Error : loading image" << std::endl;

		return 0;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(image);

	return texture;
}