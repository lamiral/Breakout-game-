#include "Sprite.h"

Sprite::Sprite(float _x, float _y, float _w,float _h,DRAW_TYPE type)
{
	this->x = _x;
	this->y = _y;
	
	w = _w;
	h = _h;

	draw_type = type;

	rect = nullptr;
	texture = 0;

	rect = new Rect(_x, _y, w,h, WITH_TEXTURE);
}

Sprite::~Sprite()
{
	freeResources();
}

void Sprite::draw()
{	
	rect->x = this->x;
	rect->y = this->y;

	if(draw_type == DYNAMIC_DRAW) rect->init_with_texture();

	glBindTexture(GL_TEXTURE_2D, texture);
		rect->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::setTexture(const char *pathTexture) 
{
	texture = TextureLoader::getTexture(pathTexture);
}

void Sprite::setTexture(GLuint _texture)
{
	texture = _texture;
}

void Sprite::setRect(Rect *r)
{
	rect = r;
}

void Sprite::freeResources()
{
	glDeleteTextures(1, &texture);
	rect->freeResources();

	delete rect;
}
