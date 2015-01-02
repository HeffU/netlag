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
*	engine.h - Engine class definition
**********************************************************************/
#pragma once

#include "utilities\platform.h"

// Global libs, TODO: check if all are really needed globally
#define GLEW_STATIC
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Eigen\Dense> // TODO: do we REALLY need more than core?


#include "scripting\scriptmanager.h"
#include "content\assetmanager.h"

namespace netlag
{
	class Engine
	{
	public:

		Engine();
		~Engine();
		int Initialize();
		int Cleanup();
		int Run();

	private:
		
		AssetManager* _assetMgr;
		ScriptManager* _scriptMgr;
		foundation::Allocator *_mainAlloc;
	};
}