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
#include "memory.h"

using namespace netlag;

Engine::Engine()
{
	
}

Engine::~Engine()
{

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

	return 0;
}

int Engine::Run()
{
	return 0;
}

int Engine::Cleanup()
{
	// Dirty trick here could be letting the OS handle all allocated memory.
	// Makes for a quicker shutdown but should it be used?

	// Probably ought to migrate all memory allocations to custom allocs
	// new / delete in the meantime for classes, malloc for PODs
	delete _assetMgr;
	delete _scriptMgr;

	foundation::memory_globals::shutdown();

	return 0;
}