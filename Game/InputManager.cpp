#include "InputManager.h"

bool InputManager::pressed(GLenum key)
{
	if (glfwGetKey(window, key) == GLFW_PRESS)
	{
		return true;
	}
}