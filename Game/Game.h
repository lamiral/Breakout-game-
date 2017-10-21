#pragma once

#include "Engine/GUI/Window.h"
#include "InputManager.h"
#include "GameManager.h"

class Game
{
private:

	Window *window;
	GameManager *game_manager;

	void clear();

public:
	
	Game(int w, int h);

	void start();
};