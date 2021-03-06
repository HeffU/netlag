/**********************************************************************
netlag - Shenanigans in Virtual Reality
Copyright(C) 2014 Rasmus Eger� <heff@heff.se>

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
#include "utilities\logging.h"
#include "memory_types.h"

// Global libs, TODO: check if all are really needed globally
#define GLEW_STATIC
#include "GL/glew.h"
#include <Eigen\Core> // TODO: do we REALLY need more than core?

namespace netlag
{
	// Forward declares:
	class ScriptManager;
	class AssetManager;
	class GLRenderer;
	class WindowManager;
	class InputManager;
	class ShaderManager;

	class Engine
	{
	public:

		Engine();
		~Engine();
		int Initialize();
		int Cleanup();
		int Run();

	private:

		bool _running;

		AssetManager* _assetMgr;
		ScriptManager* _scriptMgr;
		GLRenderer* _renderer;
		WindowManager* _windowMgr;
		InputManager* _inputMgr;
		ShaderManager* _shaderMgr;
		foundation::Allocator *_mainAlloc;
	};
}