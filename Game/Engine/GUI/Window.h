#pragma once

#include <iostream>
#include "GL\glew.h"
#include "GLFW\glfw3.h"

class Window
{
private:

	GLFWwindow *window;

public:

	Window(int w, int h, const char *title);
	~Window();

	bool is_open();

	int getWidth();
	int getHeight();

	GLFWwindow* getWindow() const;
};