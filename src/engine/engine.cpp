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
*	engine.cpp - Engine class implementation
**********************************************************************/

#include "engine.h"
#include "scripting\scriptmanager.h"
#include "content\assetmanager.h"
#include "rendering\renderer.h"
#include "memory.h"

// For temp tests:
#include "array.h"
#include "murmur_hash.h"

using namespace netlag;

Engine::Engine()
{
	if (!glfwInit()) { // TODO: log / output errors.
		exit(EXIT_FAILURE);
	}
}

Engine::~Engine()
{
	glfwTerminate();
}

int Engine::Initialize()
{
	// Initialize memory allocators
	foundation::memory_globals::init();
	_mainAlloc = &foundation::memory_globals::default_allocator();

	// Initialize asset loading
	_assetMgr = new AssetManager(_mainAlloc);

	// Initialize scripting
	_scriptMgr = new ScriptManager(_mainAlloc, _assetMgr);

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
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(_window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return EXIT_FAILURE;
	}

	_renderer = new GLRenderer(_mainAlloc);

	return 0;
}

int Engine::Run()
{
	// Temp tests.
	char* path = "test.lua";
	foundation::Array<char*> list(*_mainAlloc);
	foundation::array::push_back(list, path);
	_assetMgr->LoadFileList(list);
	uint64_t handle = foundation::murmur_hash_64
		(path, sizeof("test.lua")-1, 0);
	_scriptMgr->RunScript(handle);
	//_scriptMgr->RunString("print('Scriptmanager Initializing..');");

	while (!_scriptMgr->StateAvailable(0));

	_assetMgr->UnloadFileList(list);
	foundation::array::clear(list);

	// Main running loop:
	while (!glfwWindowShouldClose(_window))
	{

		_renderer->Render();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	return 0;
}

int Engine::Cleanup()
{
	// Dirty trick here could be letting the OS handle all allocated memory.
	// Makes for a quicker shutdown but should it be used?

	// Probably ought to migrate all memory allocations to custom allocs
	// new / delete in the meantime for classes, malloc for PODs

	glfwDestroyWindow(_window);

	delete _assetMgr;
	delete _scriptMgr;

	foundation::memory_globals::shutdown();

	return 0;
}