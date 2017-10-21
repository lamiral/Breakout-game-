#pragma once

#include "Sprite.h"
#include "Rect.h"

class Player
{
private:

	Sprite *sprite;

public:

	int lives;
	int points;

	float player_w, player_h;
	float x, y;

	Player(float x,float y,float w,float h);
	~Player();

	void setTexture(const char *filepath);
	void draw();
};