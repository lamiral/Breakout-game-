#include "Sands.h"

Sands::Sands(float _w, float _h, float _w_sand, float _h_sand)
{
	w = _w;
	h = _h;

	w_sand = _w_sand;
	h_sand = _h_sand;

	init();
}

void Sands::init()
{	
	float param = 0;
		
	unsigned int texture = TextureLoader::getTexture("Textures/brick.png");

	for(float y = 100;y < h - 200;y+=h_sand)
	{
		for(float x = param;x < (w - param);x+=w_sand)
		{
			Sprite *sprite = new Sprite(x, y, w_sand, h_sand);
			sprite->setTexture(texture);

			bricks.push_back(sprite);
		}
		param += w_sand;
	}
}

void Sands::draw()
{	
	std::cout << bricks.size() << std::endl;

	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->draw();
	}
}