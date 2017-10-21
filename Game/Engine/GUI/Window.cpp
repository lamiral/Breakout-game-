#include "Window.h"

Window::Window(int w, int h, const char *title)
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Error : GLFW_FALSE" << std::endl;

		window = nullptr;
		return;
	}

	window = glfwCreateWindow(w, h, title, NULL, NULL);

	if (!window)
	{
		std::cout << "Error : window did not create" << std::endl;

		window = nullptr;
		return;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error : GLEW_OK - false" << std::endl;

		return;
	}
}

Window::~Window()
{
	glfwTerminate();
	glfwDestroyWindow(window);
}

bool Window::is_open()
{
	glfwPollEvents();
	glfwSwapBuffers(window);

	return !glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() const
{
	return window;
}

int Window::getWidth()
{
	int w, h;
	glfwGetWindowSize(window, &w, &h);

	return w;
}

int Window::getHeight()
{
	int w, h;
	glfwGetWindowSize(window, &w, &h);

	return h;
}