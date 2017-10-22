#include "Player.h"

Player::Player(float _x,float _y,float w,float h)
{	
	x = _x;
	y = _y;
	
	player_w = w;
	player_h = h;

	sprite = new Sprite(x, y, w,h,DYNAMIC_DRAW);
}

Player::~Player()
{
	delete sprite;
}

void Player::setTexture(const char *filepath)
{
	sprite->setTexture(filepath);
}

void Player::draw()
{	
	sprite->x = x;
	sprite->y = y;

	sprite->draw();
}