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

#include "assetmanager.h"
#include "murmur_hash.h"
#include "hash.h"

#include <cstdio>

using namespace netlag;
using namespace foundation;

AssetManager::AssetManager(Allocator* alloc)
	:_alloc(alloc),
	_assets(Hash<asset_info>(*alloc))
{
	
}

AssetManager::~AssetManager()
{
	hash::clear(_assets);
}

int AssetManager::LoadFileList(Array<char*> list)
{
	return 0;
}

int AssetManager::UnloadFileList(Array<char*> list)
{
	return 0;
}

int AssetManager::_loadAsset(char* path)
{
	asset_info asset;
	asset.path = path;
	asset.handle = foundation::murmur_hash_64(path, std::strlen(path), 0);

	// Check if file exists in filesystem
	// if so, start loading?

	// parse type from first byte
	// get hashed handle from path

	// read second byte to see size needed
	// allocate and call the proper loader
}