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
#include "asset_types.h"

namespace netlag
{
	typedef asset_info(*ds_func)(char*, int);

	// Deserializer for lua script files.
	asset_info ds_luascript(char* data, int size);
	// Deserializer for a scene defenition file.
	asset_info ds_scenedef(char* data, int size);
	// Deserializer for a dialo file.
	asset_info ds_dialog(char* data, int size);
}