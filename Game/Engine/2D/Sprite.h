#pragma once

#include "Rect.h"
#include "TextureLoader.h"

//Small optimization
enum DRAW_TYPE
{
	STATIC_DRAW,
	DYNAMIC_DRAW
};

class Sprite
{
private:

	GLuint texture;
	Rect *rect;
	
	DRAW_TYPE draw_type;

public:
	
	float x, y, w, h;

	Sprite(float _x, float _y, float w,float h,DRAW_TYPE type);
	~Sprite();

	void draw();

	void setRect(Rect *_r);

	void setTexture(const char *pathTexture);
	void setTexture(GLuint _texture);

	void freeResources();
};