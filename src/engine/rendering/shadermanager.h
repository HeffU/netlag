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
*	shadermanager.h - Shadermanager class definition
**********************************************************************/
#pragma once

#include "..\engine.h"
#include "collection_types.h"
#include "rendertypes.h"

namespace netlag
{

	class ShaderManager
	{
	public:

		ShaderManager(foundation::Allocator* alloc);
		~ShaderManager();

		uint64_t CreateProgram(uint64_t vs, uint64_t gs, uint64_t fs);
		void DestroyProgram(uint64_t program);
		void RecompileProgram(uint64_t program);
		ShaderProgram GetProgram(uint64_t program);

	private:

		GLuint _compileProgram
			(const char* vs, const char* gs, const char* fs);

		foundation::Allocator *_alloc;
		foundation::Hash<ShaderProgram> _shaders;
	};
}