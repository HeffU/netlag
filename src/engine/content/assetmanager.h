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
*	assetmanager.h - AssetManager class definition
**********************************************************************/
#pragma once
#include <collection_types.h>
#include "asset_types.h"
#include "asset_loaders.h"

namespace netlag
{

	class AssetManager
	{
	public:
		AssetManager(foundation::Allocator* alloc);
		~AssetManager();

		int LoadFileList(foundation::Array<char*> list);
		int UnloadFileList(foundation::Array<char*> list);

	private:
		ds_func _loaders[asset_type::NUM_ASSET_TYPES];
		int _loadAsset(char* path);

		//TODO: Add support for loading compressed / compiled data etc.
		
		foundation::Allocator* _alloc;
		foundation::Hash<asset_info> _assets;
		foundation::Hash<int> _assetExts;
	};
}