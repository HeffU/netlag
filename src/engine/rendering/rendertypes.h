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
*	rendertypes.h - Data types for rendering
**********************************************************************/
#pragma once
#include "..\engine.h"
#include "collection_types.h"

struct ShaderProgram
{
	GLuint glProgram = -1;
	// source files from assetmanager
	uint64_t vs_src = 0;
	uint64_t gs_src = 0;
	uint64_t fs_src = 0;
};

struct ModelRenderDef {
	uint64_t shaderprogram = 0;
	GLuint vao = 0;
	GLuint verts = 0;
	GLuint vbo = 0;
	GLuint vbo_size = 0;
	GLuint vbo_offset = 0;
	GLuint num_instances = 0;
	
	uint64_t id;
	uint64_t texture;

	GLenum drawType;
	GLint drawStart;
	GLint drawCount;
};

struct ShaderInstance
{
	GLuint glProgram = -1;
	foundation::Array<ModelRenderDef> *renderDefs;
};

struct ModelInstance {
	//ModelRenderDef* model;
	Eigen::Matrix4f transform;
};