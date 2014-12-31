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
*	scriptmanager.h - Scriptmanager class definition
**********************************************************************/
#pragma once

#include <collection_types.h>
#include <thread>
#include <mutex>
#include "../content/asset_types.h"
#include "../content/assetmanager.h"

extern "C"
{
#include <lua.h>
}

namespace netlag
{
	struct luaenv
	{
		lua_State* state = nullptr;
		std::thread* thread = nullptr;
		std::mutex* mutex;
	};

	class ScriptManager
	{
	public :
		ScriptManager(foundation::Allocator* alloc, AssetManager* assetMgr);
		~ScriptManager();

		//Run a script in a certain lua state, by default state 0.
		//Returns an error if the state's thread is busy
		int RunScript(uint64_t handle, int state_id = 0);
		//Run a string of lua, defaults to state 0.
		int RunString(char* lua, int state_id = 0);

		bool StateAvailable(unsigned int state_id);

		int NewState(bool init = true);

	private :

		int _runLua(luaenv env, luascript script);

		foundation::Allocator* _alloc;
		foundation::Array<luaenv> _envs;
		AssetManager* _assetMgr;
	};

	// Custom module loader that looks inside the asset/resource manager
	// Adds the "require" functionality to packaged scripts
	extern "C" int get_packaged_module(lua_State *state);
}