#include "GameManager.h"

GameManager::GameManager(int _w,int _h,GLFWwindow *window)
{
	w = _w;
	h = _h;

	i_manager = new InputManager(window);

	player = new Player(w/2,h - 10,120,10);
	player->setTexture("Textures/Player.jpg");
	player->lives = 3;
	player->points = 0;

	ball = new Ball;
	ball->sprite = new Sprite(w / 2, h / 2, 10, 10);
	ball->sprite->setTexture("Textures/fancy-ball.png");
	
	ball->speed_x = -5;
	ball->speed_y = -5;
	ball->w = 10;
	ball->h = 10;

	background = new Sprite(0.0, h, w,h);
	background->setTexture("Background.jpg");

	sands = new Sands(w,h, 50, 20);

	shader = new Shader();
	shader->loadShaders("VertexShader.txt", "FragmentShader.txt", LOAD_FROM_FILE);

	initMatrix();
}

GameManager::~GameManager()
{
	delete player;
	delete i_manager;
	delete ball;
	delete sands;
}

void GameManager::initMatrix()
{
	glm::mat4 projection = glm::ortho(0.0f, (float)w, (float)h, 0.0f,-1.0f,1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	Ortho = projection * model;
}

void GameManager::renderGame()
{	
	shader->use();
	shader->SetMatrix4fv("Ortho", Ortho);

	//Draw game objects
	//background->draw();
	sands->draw();
	player->draw();
	ball->sprite->draw();
}

void GameManager::gameEvents()
{
	if (i_manager->pressed(GLFW_KEY_D))
	{
		if ((player->x + player->player_w) < w)
		{
			player->x += PLAYER_SPEED;
		}
	}
	else if (i_manager->pressed(GLFW_KEY_A))
	{
		if ((player->x) > 0)
		{
			player->x -= PLAYER_SPEED;
		}
	}

	chek_collision();
}

void GameManager::ball_collision()
{
	float x = ball->sprite->x, y = ball->sprite->y;

	if ((x >= player->x && x <= (player->x + player->player_w)) && y >= (player->y - player->player_h))
	{
		ball->speed_y = -ball->speed_y;
		if(Random::random(10) > 5)ball->speed_x = -ball->speed_x;
	}

	if ((x+ball->w) >= w || x <= 0) ball->speed_x = -ball->speed_x;
	
	if (y + ball->h >= h)
	{	
		player->lives--;
		if (Random::random(10) > 5)	ball->speed_x = -ball->speed_x;
		ball->speed_y = -ball->speed_y;
	}
	else if (y <= 0)
	{	
		if (Random::random(10) > 5)ball->speed_x = -ball->speed_x;
		ball->speed_y = -ball->speed_y;
	}

	ball->sprite->x += ball->speed_x;
	ball->sprite->y += ball->speed_y;
}

void GameManager::chek_collision()
{
	ball_collision();
	brick_collision();
}

void GameManager::brick_collision()
{
	int bricks_size = sands->bricks.size();

	float b_x = ball->sprite->x;
	float b_y = ball->sprite->y;
	float b_w = ball->w;
	float b_h = ball->h;

	for (int i = 0; i < bricks_size; i++)
	{	
		Sprite *brick = sands->bricks[i];

		if ((b_x > brick->x && b_x < brick->x + brick->w) && ((b_y > brick->y && b_y < brick->y + brick->h) ||(b_y > brick->y + brick->h && b_y < brick->y)))
		{
			sands->bricks.erase(sands->bricks.begin() + i);
			bricks_size--;

			if (Random::random(10) > 5)ball->speed_x = -ball->speed_x;
			ball->speed_y = -ball->speed_y;

			continue;
		}
	}
}