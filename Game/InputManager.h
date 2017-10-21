#pragma once

#include <GLFW\glfw3.h>

class InputManager
{
private:

	GLFWwindow *window;

public:

	InputManager(GLFWwindow *_window) : window(_window) {};

	bool pressed(GLenum key);

};