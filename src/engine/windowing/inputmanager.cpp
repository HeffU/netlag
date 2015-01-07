/**********************************************************************
netlag - Shenanigans in Virtual Reality
Copyright(C) 2014 Rasmus Egerö <heff@heff.se>

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/
***********************************************************************
*	inputmanager.h - Inputmanager implementation
**********************************************************************/

#include "inputmanager.h"

#include "..\utilities\platform.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

using namespace netlag;

int InputManager::Initialize(GLFWwindow* window)
{
	// TODO: make input window specific, store inputs in a hash
	// containing the windows or something like that.

	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetKeyCallback(window, KeyPressCallback);

	return 0;
}

int InputManager::Cleanup(GLFWwindow* window)
{

	return 0;
}

int InputManager::Update()
{
	glfwPollEvents();

	return 0;
}

void InputManager::MouseButtonCallback
	(GLFWwindow* window, int button, int action, int mods)
{

}

void InputManager::CursorPositionCallback
	(GLFWwindow* window, double xpos, double ypos)
{

}

void InputManager::ScrollCallback
	(GLFWwindow* window, double xoffset, double yoffset)
{

}

void InputManager::KeyPressCallback
	(GLFWwindow* window, int key, int scancode, 
									int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}