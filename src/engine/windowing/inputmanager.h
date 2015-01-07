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
*	inputmanager.h - Inputmanager class definition
**********************************************************************/
#pragma once

#include "memory_types.h"

struct GLFWwindow;

namespace netlag
{

	class InputManager
	{
	public :
		InputManager(foundation::Allocator* alloc);
		~InputManager();

		int Update();

		int Initialize(GLFWwindow* window);
		int Cleanup(GLFWwindow* window);

		static InputManager* GetInstance();

		static void MouseButtonCallback
			(GLFWwindow* window, int button, int action, int mods);
		static void CursorPositionCallback
			(GLFWwindow* window, double xpos, double ypos);
		static void ScrollCallback
			(GLFWwindow* window, double xoffset, double yoffset);
		static void KeyPressCallback
			(GLFWwindow* window, int button, int scancode, 
											int action, int mods);

	private :

		static InputManager* _instance;

		foundation::Allocator* _alloc;
		
	};
}
