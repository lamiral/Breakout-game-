#include "Breakouts.h"

Breakouts::Breakouts(float _w, float _h, float _w_sand, float _h_sand)
{
	w = _w;
	h = _h;

	w_breakout = _w_sand;
	h_breakout = _h_sand;

}

Breakouts::~Breakouts()
{
	freeBreakouts();
}

void Breakouts::freeBreakouts()
{
	short breaks_size = breakouts.size();

	for (int i = 0; i < breaks_size; i++)
	{
		delete breakouts[0];
		breakouts.erase(breakouts.begin());
	}
}

void Breakouts::init(std::string pathTexture)
{
	this->init(pathTexture.c_str());
}

void Breakouts::init(const char *pathTexture)
{	
	freeBreakouts();

	float param = 0;
		
	unsigned int texture = TextureLoader::getTexture(pathTexture);
	
	for(float y = 100;y < h - 200;y+=h_breakout)
	{
		for(float x = param;x < (w - param);x+=w_breakout)
		{
			Sprite *sprite = new Sprite(x, y, w_breakout, h_breakout,STATIC_DRAW);
			sprite->setTexture(texture);

			breakouts.push_back(sprite);
		}
		param += w_breakout;
	}
}

void Breakouts::draw()
{	
	for (int i = 0; i < breakouts.size(); i++)
	{
		breakouts[i]->draw();
	}
}