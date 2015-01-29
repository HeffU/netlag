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
#include "asset_types.h"

namespace netlag
{
	typedef char* (*ds_func)(asset_info, foundation::Allocator*);
	typedef int (*ul_func)(asset_info, foundation::Allocator*);

	// TODO: for now, its assumed that all target platforms are set to
	// little-endian. In case this ever changes, this needs an overhaul

	// Deserializer for lua script files.
	char* ds_luascript(asset_info info, foundation::Allocator* alloc);
	// Deserializer for a scene defenition file.
	char* ds_scenedef(asset_info info, foundation::Allocator* alloc);
	// Deserializer for a dialog file.
	char* ds_dialog(asset_info info, foundation::Allocator* alloc);
	// Deserializer for text files
	char* ds_textfile(asset_info info, foundation::Allocator* alloc);

	// Cleanup for lua script files.
	int ul_luascript(asset_info info, foundation::Allocator* alloc);
	// Cleanup for a scene defenition file.
	int ul_scenedef(asset_info info, foundation::Allocator* alloc);
	// Cleanup for a dialog file.
	int ul_dialog(asset_info info, foundation::Allocator* alloc);
	// Cleanup for text files
	int ul_textfile(asset_info info, foundation::Allocator* alloc);
}