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
*	assetmanager.cpp - AssetManager implementaion
**********************************************************************/

#include "../asset_loaders.h"
#include "memory.h"

using namespace netlag;
using namespace foundation;

char* netlag::ds_luascript(asset_info info, Allocator* alloc)
{
	luascript* script = (luascript*)alloc->allocate(sizeof(luascript));
	// As the script is already allocated, simply redirect pointers.
	script->data = (char*)info.asset;
	// TODO: define / specify this
	script->chunkname = "netlag";
	script->size = info.filesize;

	return (char*)script;
}

char* netlag::ds_scenedef(asset_info info, Allocator* alloc)
{
	return nullptr;
}

char* netlag::ds_dialog(asset_info info, Allocator* alloc)
{
	return nullptr;
}