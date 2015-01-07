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
#include "windowing\windowmanager.h"
#include "windowing\inputmanager.h"
#include "utilities\logging.h"

#include "memory.h"

// For temp tests:
#include "array.h"
#include "murmur_hash.h"

using namespace netlag;

Engine::Engine()
{
	utilities::log_start();
	// Initialize memory allocators
	foundation::memory_globals::init();
	_mainAlloc = &foundation::memory_globals::default_allocator();
}

Engine::~Engine()
{
	foundation::memory_globals::shutdown();

	utilities::log_stop();
}

int Engine::Initialize()
{
	// Initialize asset loading
	_assetMgr = new AssetManager(_mainAlloc);

	// Initialize scripting
	_scriptMgr = new ScriptManager(_mainAlloc, _assetMgr);

	// Initialize window management
	_windowMgr = new WindowManager(_mainAlloc);
	_windowMgr->Initialize();

	// Initialize window input
	_inputMgr = &InputManager::GetInstance();
	_windowMgr->InitializeInput();

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

	_running = true;


	// Main loop:
	while (_running)
	{
		_renderer->Render();

		_inputMgr->Update();
		if (_windowMgr->Update() == -1)
			_running = false;
	}

	return 0;
}

int Engine::Cleanup()
{
	// Dirty trick here could be letting the OS handle all allocated memory.
	// Makes for a quicker shutdown but should it be used?

	// Probably ought to migrate all memory allocations to custom allocs
	// new / delete in the meantime for classes, malloc for PODs

	_windowMgr->Cleanup();
	delete _windowMgr;

	delete _assetMgr;
	delete _scriptMgr;

	return 0;
}