#pragma once

#include "GL/glew.h"
#include "GLFW\glfw3.h"

#include "InputManager.h"
#include "Player.h"
#include "Engine/Shaders/Shader.h"
#include "Engine/Utils/Random.h"
#include "Sands.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define PLAYER_SPEED 10

struct Ball
{
	Sprite *sprite;

	float speed_x, speed_y;
	float w, h;
};

class GameManager
{
private:

	InputManager *i_manager;
	Shader *shader;

	Player *player;
	Ball *ball;
	Sprite *background;
	Sands *sands;

	int w, h;

	glm::mat4 Ortho;

	void initMatrix();

	void ball_collision();
	void brick_collision();

	void chek_collision();

public:

	GameManager(int w, int h,GLFWwindow *window);
	~GameManager();

	void gameEvents();
	void renderGame();
};