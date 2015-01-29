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
*	asset_types.h - Definitions of asset types / structs
**********************************************************************/
#pragma once
#include <collection_types.h>

namespace netlag
{
	enum asset_type
	{
		// scripts
		LUA_SCRIPT,

		// scenes
		SCENE_DEFENITION,
		
		// dialog
		DIALOG,

		// shaders
		VERTEX_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,

		// misc
		INVALID,
		NUM_ASSET_TYPES
		// Invalid should never be present past initialization.
	};

	struct asset_info
	{
		int _refcount = 0;
		//int version = 0; // Is this needed?
		asset_type _type = INVALID;
		void* asset = nullptr;
		char* path = nullptr;
		uint64_t handle = 0;
		int filesize = 0;
	};

	// Represents lua code to be loaded into a lua state
	struct luascript
	{
		char* chunkname = nullptr;
		char* data = nullptr;
		unsigned int size = 0;
	};
}