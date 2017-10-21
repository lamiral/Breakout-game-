#include "Sprite.h"

Sprite::Sprite(float _x, float _y, float _w,float _h)
{
	this->x = _x;
	this->y = _y;
	
	w = _w;
	h = _h;

	rect = nullptr;
	texture = 0;

	rect = new Rect(_x, _y, w,h, WITH_TEXTURE);
}

Sprite::~Sprite()
{
	delete rect;
}

void Sprite::draw()
{	
	rect->x = this->x;
	rect->y = this->y;

	rect->init_with_texture();

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
