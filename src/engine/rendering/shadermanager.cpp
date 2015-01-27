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

using namespace netlag;
using namespace foundation;


ShaderManager::ShaderManager(Allocator* alloc)
	:_alloc(alloc),
	_shaders(Hash<ShaderProgram>(*alloc))
{

}

ShaderManager::~ShaderManager()
{

}

uint64_t ShaderManager::CreateProgram
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

	ShaderProgram program;
	program.vs_src = vs;
	program.gs_src = gs;
	program.fs_src = fs;

	//TODO: this obv should come from the arguments rather than hardcoded.
	program.glProgram = _compileProgram(vertex_shader, 0, fragment_shader);

	//TODO: init array obv

	uint64_t id = 0;
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
	(const char* vs, const char* gs, const char* fs)
{
	GLuint shader_program = glCreateProgram();

	if (fs != 0)
	{
		GLuint _vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(_vs, 1, &vs, NULL);
		glCompileShader(_vs);
		glAttachShader(shader_program, _vs);
	}

	if (gs != 0)
	{
		// yaya.
		GLuint _gs = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(_gs, 1, &gs, NULL);
		glCompileShader(_gs);
		glAttachShader(shader_program, _gs);
	}

	if (vs != 0)
	{
		GLuint _fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(_fs, 1, &fs, NULL);
		glCompileShader(_fs);
		glAttachShader(shader_program, _fs);
	}

	glLinkProgram(shader_program);
	//glDetachShader()
	//glDeleteShader()

	return shader_program;
}