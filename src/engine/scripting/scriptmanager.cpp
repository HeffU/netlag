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
#include "array.h"
#include "hash.h"

#include "..\utilities\hashing.h"
#include "..\utilities\logging.h"

#include "../content/assetmanager.h"

extern "C"
{
#include <lauxlib.h>
#include <lualib.h>
}

using namespace netlag;
using namespace foundation;

extern "C" int get_packaged_module(lua_State *state);

ScriptManager::ScriptManager(Allocator* alloc, AssetManager* assetMgr)
	:_envs(Array<luaenv>(*alloc)),
	_alloc(alloc),
	_assetMgr(assetMgr)
{
	//LoadScript( _loader script_ );
	NewState();
}

ScriptManager::~ScriptManager()
{
	array::clear(_envs);
}

int ScriptManager::NewState(bool init)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaenv env;
	env.state = L;
	env.thread = new std::thread();
	env.mutex = new std::mutex();

	int id = array::size(_envs);
	array::push_back(_envs, env);
	if (init)
	{
		lua_register(env.state, "get_packaged_module", get_packaged_module);
		luaL_dostring(env.state, "table.insert(package.loaders, get_packaged_module)");
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


int ScriptManager::RunScript(uint64_t handle, int state_id)
{
	if (!StateAvailable(state_id))
	{
		utilities::log("[SCRIPT] Error: State not available!");
		return -1; // fix returns, error handling etc.
	}
	// Try to get the script from the assetmanager
	asset_info info = _assetMgr->GetAsset(handle);
	if (info._type == INVALID)
	{
		utilities::log("[SCRIPT] Error: Script does not exist!");
		return -2; // fix, this means the script doesnt exist in the manager
	}
	luascript* script = (luascript*)info.asset;

	luaenv env = _envs[state_id];
	*env.thread = std::thread(&ScriptManager::_runLua, this, env, *script);
	return 0;
}

int ScriptManager::RunString(char* lua, int state_id)
{
	if (!StateAvailable(state_id))
	{
		utilities::log("[SCRIPT] Error: State not available!");
		return -1; // fix returns, error handling etc.
	}

	luascript script;
	script.chunkname = "temp";
	script.data = lua;
	script.size = strlen(lua);

	luaenv env = _envs[state_id];
	*env.thread = std::thread(&ScriptManager::_runLua, this, env, script);
	return 0;
}

int ScriptManager::_runLua(luaenv env, luascript script)
{
	env.mutex->lock();
	// run script here
	int err = luaL_loadbuffer(env.state, script.data, script.size, script.chunkname);
	if (err == LUA_ERRSYNTAX)
	{
		//fix errorhandling
		utilities::log("[SCRIPT] Syntax Error: %s", lua_tostring(env.state, -1));
	}
	else if (err == LUA_ERRMEM)
	{
		//fix errorhandling
		utilities::log("[SCRIPT] Error: Lua could not allocate memory, either too low or wrong placement.");
	}
	err = lua_pcall(env.state, 0, 0, 0);

#ifdef NETLAG_DEBUG
	if (err != 0)
	{
		utilities::log("[SCRIPT] Lua output: %s", lua_tostring(env.state, -1));
	}
#endif

	env.mutex->unlock();
	return 0;
}

// Custom module loader that looks inside the asset/resource manager
// Adds the "require" functionality to packaged scripts
extern "C" int get_packaged_module(lua_State *state)
{
	// make sure this is threadsafe / the assetmanager is threadsafe!
	const char *name = luaL_checkstring(state, 1);

	// try to get script from manager
	luascript script;

	// if it exists:
	if (false) 	//TODO: add correct exist check
	{
		// propagate these errors back to lua? or ignore?
		int err = luaL_loadbuffer(state, script.data, script.size, script.chunkname);
		if (err == LUA_ERRSYNTAX)
		{
			utilities::log("[SCRIPT] Syntax Error: %s", lua_tostring(state, -1));
			//fix errorhandling
		}
		else if (err == LUA_ERRMEM)
		{
			utilities::log("[SCRIPT] Error: Lua could not allocate memory, either too low or wrong placement.");
			//fix errorhandling
		}
	}
	else 
	{
		lua_pushnil(state);
	}
	return 1;
}