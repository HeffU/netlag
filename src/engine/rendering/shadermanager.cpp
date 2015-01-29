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
*	shadermanager.cpp - Shadermanager implementaion
**********************************************************************/
#include "shadermanager.h"
#include "array.h"
#include "hash.h"

#include "../content/assetmanager.h"

using namespace netlag;
using namespace foundation;


ShaderManager::ShaderManager(Allocator* alloc, AssetManager* assetMgr)
	:_alloc(alloc),
	_shaders(Hash<ShaderProgram>(*alloc)),
	_assetMgr(assetMgr)
{

}

ShaderManager::~ShaderManager()
{
	if (array::size(_shaders._data) > 0)
	{
		uint64_t shader = hash::begin(_shaders)->key;
		uint32_t next = 0;
		while (next != -1)
		{
			DestroyProgram(shader);
			next = _shaders._data[next].next;
			shader = _shaders._data[next].key;
		}
	}
	hash::clear(_shaders);
}

uint64_t ShaderManager::CreateProgram
	(uint64_t vs, uint64_t gs, uint64_t fs)
{
	ShaderProgram program;
	program.vs_src = vs;
	program.gs_src = gs;
	program.fs_src = fs;

	program.glProgram = _compileProgram(vs, gs, fs);

	//TODO: init array obv

	uint64_t id = 1337;
	//TODO: get a fresh ID, either from some ID util or from hash?
	hash::set(_shaders, id, program);
	return id;
}

void ShaderManager::DestroyProgram(uint64_t program)
{
	ShaderProgram _program;
	_program = hash::get<ShaderProgram>(_shaders, program, _program);
	if (_program.users == nullptr)
		return;

	glDeleteProgram(_program.glProgram);

	// loop through users and invalidate shader?
	// destroy users array
	// remove from hash
}

void ShaderManager::RecompileProgram(uint64_t program)
{
	ShaderProgram _program;
	_program = hash::get<ShaderProgram>(_shaders, program, _program);
	if (_program.users == nullptr)
		return;

	glDeleteProgram(_program.glProgram);
	// TODO: get new sources from assetmgr obv.
	_program.glProgram = _compileProgram(0, 0, 0);
	// loop through users and update with new program
}

GLuint ShaderManager::_compileProgram
	(uint64_t vs, uint64_t gs, uint64_t fs)
{
	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main () {"
		"  gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main () {"
		"  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";



	GLuint shader_program = glCreateProgram();
	GLuint _vs = 0;
	GLuint _gs = 0;
	GLuint _fs = 0;

	// Try to get the sources
	asset_info vsAsset = _assetMgr->GetAsset(vs);
	asset_info gsAsset = _assetMgr->GetAsset(gs);
	asset_info fsAsset = _assetMgr->GetAsset(fs);

	if (vsAsset._type != INVALID)
	{
		_vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(_vs, 1, &vertex_shader, NULL);
		glCompileShader(_vs);
		glAttachShader(shader_program, _vs);
	}

	if (gsAsset._type != INVALID)
	{
		_gs = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(_gs, 1, (const GLchar **)&gsAsset.asset, NULL);
		glCompileShader(_gs);
		glAttachShader(shader_program, _gs);
	}

	if (fsAsset._type != INVALID)
	{
		_fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(_fs, 1, &fragment_shader, NULL);
		glCompileShader(_fs);
		glAttachShader(shader_program, _fs);
	}

	glLinkProgram(shader_program);

	if (_vs != 0)
	{
		glDetachShader(shader_program, _vs);
		glDeleteShader(_vs);
	}
	if (_gs != 0)
	{
		glDetachShader(shader_program, _gs);
		glDeleteShader(_gs);
	}
	if (_fs != 0)
	{
		glDetachShader(shader_program, _fs);
		glDeleteShader(_fs);
	}

	return shader_program;
}

ShaderProgram ShaderManager::GetProgram(uint64_t handle)
{
	ShaderProgram program;
	return hash::get<ShaderProgram>(_shaders, handle, program);
}