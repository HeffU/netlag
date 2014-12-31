/**********************************************************************
netlag - Shenanigans in Virtual Reality
Copyright(C) 2014 Rasmus Eger� <heff@heff.se>

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
#include <sys/types.h>
#include <sys/stat.h>

using namespace netlag;
using namespace foundation;

AssetManager::AssetManager(Allocator* alloc)
	:_alloc(alloc),
	_assets(Hash<asset_info>(*alloc)),
	_assetExts(Hash<int>(*alloc))
{
	// Init functions and map extensions to types.
	_loaders[0] = ds_luascript;
	hash::set(_assetExts, murmur_hash_64("lua", 3, 0), 0);

	_loaders[1] = ds_scenedef;
	hash::set(_assetExts, murmur_hash_64("sce", 3, 0), 1);

	_loaders[2] = ds_dialog;
	hash::set(_assetExts, murmur_hash_64("dia", 3, 0), 2);
}

AssetManager::~AssetManager()
{
	hash::clear(_assets);
	hash::clear(_assetExts);
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
	int len = std::strlen(path);

	asset_info asset;
	asset.path = path;
	asset.handle = murmur_hash_64(path, len, 0);


	// Check if file exists, get file stats and try to open it
	struct stat st;
	stat(path, &st);
	FILE* file = fopen(path, "r");
	if (file == NULL)
		return -1; // error handling..

	// Get the extensions handle and validate that its proper
	uint64_t typehandle = murmur_hash_64(&path[(len - 3) - 1], 3, 0);
	int type = hash::get(_assetExts, typehandle, -1);
	if (type == -1)
		return -2; // err
	asset._type = (asset_type)type;

	// alloc memory for the file, read and close.
	asset.asset = (char*)_alloc->allocate(st.st_size);
	if (fread(asset.asset, st.st_size, 1, file) != st.st_size)
		return -3; // err
	fclose(file);

	// call the proper loader and add the asset to the hash
	_loaders[type](asset);
	hash::set(_assets, asset.handle, asset);
	return 0;
}

asset_info AssetManager::GetAsset(uint64_t handle)
{
	asset_info info;
	return hash::get<asset_info>(_assets, handle, info);
}