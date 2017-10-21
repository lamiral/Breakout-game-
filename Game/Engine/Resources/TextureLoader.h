#pragma once

#include <GL/glew.h>
#include <iostream>
#include "SOIL.h"

class TextureLoader
{
public:

	static GLuint getTexture(const char *pathTexture);
};