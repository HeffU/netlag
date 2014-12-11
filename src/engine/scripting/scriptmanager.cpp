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
#include <hash.h>

using namespace netlag;
using namespace foundation;

ScriptManager::ScriptManager(Allocator* alloc)
	:_envs(Array<luaenv>(*alloc)),
	_scripts(Hash<luascript>(*alloc))
{
	//LoadScript( _loader script_ );
	NewState();
}

ScriptManager::~ScriptManager()
{
	array::clear(_envs);
	hash::clear(_scripts);
}

int ScriptManager::NewState(bool init)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaenv env;
	env.state = L;
	env.thread = new std::thread();

	int id = array::size(_envs);
	array::push_back(_envs, env);
	if (init)
	{
		//RunScript(loader script handle, id);
	}
	return id;
}

bool ScriptManager::StateAvailable(unsigned int state_id)
{
	// TODO: this mutex system is no good,
	// fix if this is ever a problem
	if (state_id >= array::size(_envs))
		return false;
	if (!_envs[state_id].mutex->try_lock())
		return false;
	_envs[state_id].mutex->unlock();
	return true;
}

uint64_t ScriptManager::LoadScript(unsigned char* path, unsigned int len)
{
	uint64_t handle = foundation::murmur_hash_64(path, len, 0);
	// get script from assetmanager
}

int ScriptManager::RunScript(uint64_t handle, int state_id)
{
	if (!StateAvailable(state_id))
		return -1; // fix returns, error handling etc.
	luascript script;
	script = hash::get(_scripts, handle, script);
	if (script.path == nullptr)
		return -2; // fix, this means the script doesnt exist in the manager
	// Update this to correctly work with concurrent access to a single script
	// once the resource manager is active
	luaenv env = _envs[state_id];
	*env.thread = std::thread(&ScriptManager::_runLua, env, script);
}

void ScriptManager::_runLua(luaenv env, luascript script)
{
	env.mutex->lock();
	// run script here
	env.mutex->unlock();
}

void ScriptManager::TerminateState(unsigned int state)
{
	// needed? feasible?
}