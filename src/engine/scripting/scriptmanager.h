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

namespace netlag
{
	struct luaenv
	{
		bool idle = true;
		lua_State* state = nullptr;
		std::thread* thread = nullptr;
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

		void TerminateScript(uint64_t handle);
		void TerminateState(int state);

		int NewState(bool init = true);

	private :

		foundation::Array<luaenv> _envs;
	};
}