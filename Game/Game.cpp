#include "Game.h"

Game::Game(int w, int h)
{
	window = new Window(w, h, "Under");

	game_manager = new GameManager(w, h,window->getWindow());
}

void Game::start()
{
	while (window->is_open())
	{
		clear();
		game_manager->gameEvents();
		game_manager->renderGame();
	}
}

void Game::clear()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}