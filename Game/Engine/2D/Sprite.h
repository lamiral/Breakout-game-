#pragma once

#include "../Primitives/Rect.h"
#include "../Resources/TextureLoader.h"

class Sprite
{
private:

	GLuint texture;
	Rect *rect;
	
public:
	
	float x, y, w, h;

	Sprite(float _x, float _y, float w,float h);
	~Sprite();

	void draw();

	void setRect(Rect *_r);

	void setTexture(const char *pathTexture);
	void setTexture(GLuint _texture);
};