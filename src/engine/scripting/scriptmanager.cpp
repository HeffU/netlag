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
#include "../utilities/hashing.h"

using namespace netlag;

ScriptManager::ScriptManager()
{

}

ScriptManager::~ScriptManager()
{

}

uint64_t ScriptManager::LoadScript(unsigned char* path)
{
	uint64_t handle = utilities::djb2hash(path);
}

int ScriptManager::RunScript(uint64_t handle, int state_id)
{

}