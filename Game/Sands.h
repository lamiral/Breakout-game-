#pragma once

#include <iostream>
#include <vector>
#include "Sprite.h"
#include "TextureLoader.h"

class Sands
{
private:
	
	float w, h;

	void init();

public:

	std::vector<Sprite*> bricks;

	float w_sand, h_sand;
	Sands(float w, float h, float w_sand, float h_sand);

	void draw();
};