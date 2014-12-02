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
#include <lua.h>
#include <thread>
#include <mutex>

namespace netlag
{
	struct luaenv
	{
		lua_State* state = nullptr;
		std::thread* thread = nullptr;
		std::mutex* mutex;
	};

	struct luascript
	{
		unsigned char* path = nullptr;
	};

	class ScriptManager
	{
	public :
		ScriptManager(foundation::Allocator* alloc);
		~ScriptManager();
		uint64_t LoadScript(unsigned char* path, unsigned int len);

		//Run a script in a certain lua state, by default state 0.
		//Returns an error if the state's thread is busy
		int RunScript(uint64_t handle, int state_id = 0);

		bool StateAvailable(unsigned int state_id);

		void TerminateScript(uint64_t handle);
		void TerminateState(unsigned int state);

		int NewState(bool init = true);

	private :

		void _runLua(luaenv env, luascript script);

		foundation::Hash<luascript> _scripts;
		foundation::Array<luaenv> _envs;
	};
}