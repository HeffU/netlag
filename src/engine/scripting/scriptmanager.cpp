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
*	scriptmanager.cpp - Scriptmanager implementation
**********************************************************************/

#include "scriptmanager.h"
#include "murmur_hash.h"
#include <lauxlib.h>
#include <lualib.h>
#include <array.h>

using namespace netlag;
using namespace foundation;

ScriptManager::ScriptManager(Allocator* alloc)
	:_envs(Array<luaenv>(*alloc))
{
	NewState();
}

ScriptManager::~ScriptManager()
{

}

int ScriptManager::NewState(bool init)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaenv env;
	env.state = L;
	env.thread = new std::thread();

	if (init)
	{
		//run bootstrap script to load all game libs here
	}

	array::push_back(_envs, env);
	return array::size(_envs) - 1;
}

uint64_t ScriptManager::LoadScript(unsigned char* path, unsigned int len)
{
	uint64_t handle = foundation::murmur_hash_64(path, len, 0);
}

int ScriptManager::RunScript(uint64_t handle, int state_id)
{

}

void ScriptManager::TerminateScript(uint64_t handle)
{

}

void ScriptManager::TerminateState(int state)
{

}