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
*	windowmanager.h - Windowmanager implementation
**********************************************************************/

#include "windowmanager.h"
#include "inputmanager.h"
#include "memory.h"
#include "..\utilities\logging.h"

#include "..\utilities\platform.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

using namespace netlag;
using namespace foundation;

WindowManager::WindowManager(Allocator* alloc)
	:_alloc(alloc)
{

}

WindowManager::~WindowManager()
{

}

int WindowManager::Initialize()
{
	if (!glfwInit()) { // TODO: log / output errors.
		return -1;
	}

	// TODO: move window creation to its own function,
	// makes more sense and could support more windows.
	// Initialize the window
	glfwWindowHint(GLFW_DEPTH_BITS, 16);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef PLATFORM_OS_OSX
	// Quick fix for Mac
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	_window = glfwCreateWindow(640, 480, "netlag", NULL, NULL);
	if (!_window)
	{
		utilities::log("[WINDOW] Error: Failed to create window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(_window);

	return 0;
}

int WindowManager::InitializeInput()
{
	InputManager::GetInstance().Initialize(_window);
	
	return 0;
}

int WindowManager::Cleanup()
{
	glfwDestroyWindow(_window);

	glfwTerminate();

	return 0;
}

int WindowManager::Update()
{
	if (glfwWindowShouldClose(_window))
		return -1;

	glfwSwapBuffers(_window);

	return 0;
}