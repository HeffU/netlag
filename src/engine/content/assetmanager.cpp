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
#include "asset_loaders.h"
#include "murmur_hash.h"
#include "hash.h"

#include <cstdio>

using namespace netlag;
using namespace foundation;

AssetManager::AssetManager(Allocator* alloc)
	:_alloc(alloc),
	_assets(Hash<asset_info>(*alloc))
{
	_loaders[0] = ds_luascript;
	_loaders[1] = ds_scenedef;
	_loaders[2] = ds_dialog;
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
	FILE* file = fopen(path, "r");
	// if so, start loading?
	if (file == NULL)
		return -1; // error handling..

	asset_header header;
	// parse asset header for type and size
	fread(&header, sizeof(asset_header), 1, file);

	// Check that the type is in the valid range
	if (header.type < 0 || header.type > NUM_ASSET_TYPES)
		return -2; // err
	asset._type = (asset_type)header.type;

	// alloc memory for the rest of the file and read that.
	asset.asset = (char*)_alloc->allocate(header.filesize);
	if (fread(asset.asset, header.filesize, 1, file) != header.filesize)
		return -3; // err

	//TODO: fix this hardcoded shit, only works for luascripts at this point.

	// call the proper loader
	_loaders[header.type](asset);

	// add asset to the list
	hash::set(_assets, asset.handle, asset);
	return 0;
}