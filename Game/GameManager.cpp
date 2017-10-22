#include "GameManager.h"

GameManager::GameManager(int _w,int _h,GLFWwindow *window)
{
	w = _w;
	h = _h;

	lvl = 0;

	i_manager = new InputManager(window);

	player = new Player(w / 2, h - 10, 120, 10);
	player->setTexture("Textures/Player2.png");

	ball = new Ball;
	ball->sprite = new Sprite(w / 2, h / 2, 10, 10,DYNAMIC_DRAW);
	ball->sprite->setTexture("Textures/ball.png");

	background = new Sprite(0.0f,0.0f, w, h,STATIC_DRAW);
	background->setTexture("Textures/space.jpg");

	ball->accel = 2.0f;

	breakouts = new Breakouts(w, h, 50, 20);
	breakouts->init("Textures/s5.png");

	startInit();

	shader = new Shader();
	shader->loadShaders("VertexShader.txt", "FragmentShader.txt", LOAD_FROM_FILE);

	initMatrix();
}

GameManager::~GameManager()
{
	delete player;
	delete i_manager;
	delete ball;
	delete breakouts;
}

void GameManager::initMatrix()
{
	glm::mat4 projection = glm::ortho(0.0f, (float)w, (float)h, 0.0f,-1.0f,1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	Ortho = projection * model;
}

void GameManager::startInit()
{	
	if (lvl == 8) lvl = 0;

	lvl++;
	player->lives = 3;
	player->points = 0;
	
	ball->sprite->x = player->x + 50;
	ball->sprite->y = player->y - 50;

	ball->accel += 0.3;
	ball->speed_x = -ball->accel;
	ball->speed_y = -ball->accel;
	ball->w = 10;
	ball->h = 10;
	
	std::stringstream s;

	s << "Textures/Breakouts/" << lvl << ".png";
	std::string str = s.str();
	breakouts->init(str);
}

void GameManager::renderGame()
{	
	shader->use();
	shader->SetMatrix4fv("Ortho", Ortho);

	//Draw game objects
	background->draw();
	breakouts->draw();
	player->draw();
	ball->sprite->draw();
}

void GameManager::playerKey()
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
}

void GameManager::gameEvents()
{
	playerKey();
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
	int bricks_size = breakouts->breakouts.size();

	float b_x = ball->sprite->x;
	float b_y = ball->sprite->y;
	float b_w = ball->w;
	float b_h = ball->h;

	for (int i = 0; i < bricks_size; i++)
	{	
		Sprite *brick = breakouts->breakouts[i];

		if ((b_x > brick->x && b_x < brick->x + brick->w) && ((b_y > brick->y && b_y < brick->y + brick->h) ||(b_y > brick->y + brick->h && b_y < brick->y)))
		{
			breakouts->breakouts.erase(breakouts->breakouts.begin() + i);

			if (Random::random(10) > 5)ball->speed_x = -ball->speed_x;
			ball->speed_y = -ball->speed_y;

			player->points += 5;

			std::cout << "boom" << std::endl;
			std::cout <<"Bricks size  = " << breakouts->breakouts.size() << std::endl;
			
			if (player->points >= 50)startInit();
			break;
		}
	}
}