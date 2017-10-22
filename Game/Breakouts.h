#pragma once

#include <iostream>
#include <vector>
#include "Sprite.h"
#include "TextureLoader.h"

class Breakouts
{
private:
	
	float w, h;

	void freeBreakouts();

public:

	Breakouts(float w, float h, float w_sand, float h_sand);
	~Breakouts();

	void init(const char *pathTexture);
	void init(std::string pathTexture);

	std::vector<Sprite*> breakouts;

	float w_breakout, h_breakout;

	void draw();
};