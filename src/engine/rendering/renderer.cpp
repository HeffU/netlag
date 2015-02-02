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
*	renderer.cpp - Renderer implementaion
**********************************************************************/
#include "renderer.h"
#include "shadermanager.h"
#include "hash.h"
#include "array.h"

using namespace netlag;
using namespace foundation;

GLRenderer::GLRenderer(Allocator* alloc, ShaderManager* shaders)
	:_alloc(alloc),
	_shaderMgr(shaders),
	_instanceRenders(Hash<ShaderInstance>(*alloc))
{
	/******************************************/

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	utilities::log("[RENDERER] Renderer: %s", renderer);
	utilities::log("[RENDERER] OpenGL version supported %s", version);

	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
}

GLRenderer::~GLRenderer()
{
	uint32_t next = 0;
	int size = 0;
	ShaderInstance inst;
	ModelRenderDef def;
	if (array::size(_instanceRenders._data) > 0)
	{
		inst = hash::begin(_instanceRenders)->value;
		while (next != -1)
		{
			array::clear(*inst.renderDefs);
			delete inst.renderDefs;
			next = _instanceRenders._data[next].next;
		}
		hash::clear(_instanceRenders);
	}
}

int GLRenderer::Initialize()
{
	/*float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
	};*/

	Eigen::Matrix3f verts;
	verts <<
		0.0f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.0f, 0.0f, 0.0f;

	float posdata[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.3f, 0.0f
	};

	Eigen::Matrix<float, 2, 3> positions(posdata);

	ModelRenderDef def;

	glGenVertexArrays(1, &def.vao);
	glBindVertexArray(def.vao);

	// verts
	glGenBuffers(1, &def.verts);
	glBindBuffer(GL_ARRAY_BUFFER, def.verts);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(verts.data()), verts.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &def.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, def.vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(positions.data()), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glVertexAttribDivisor(1, 1);

	def.num_instances = 2;

	AddInstancedShader(1337);
	def.shaderprogram = 1337;
	AddRenderDef(def);

	return 0;
}

int GLRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	uint32_t next = 0;
	int size = 0;
	ShaderInstance inst;
	ModelRenderDef def;
	if (array::size(_instanceRenders._data) > 0)
	{
		inst = hash::begin(_instanceRenders)->value;
		glUseProgram(inst.glProgram);
		while (next != -1)
		{
			size = array::size(*inst.renderDefs);
			for (int n = 0; n < size; n++)
			{
				def = (*inst.renderDefs)[n];
				glBindVertexArray(def.vao);
				glDrawArraysInstanced(GL_TRIANGLES, 
					0, 3, def.num_instances);
			}
			next = _instanceRenders._data[next].next;
		}
	}
	return 0;
}

int GLRenderer::AddRenderDef(ModelRenderDef& def)
{
	ShaderInstance inst;
	inst = hash::get(_instanceRenders, def.shaderprogram, inst);
	if (inst.glProgram == -1)
		return -1;

	array::push_back(*inst.renderDefs, def);

	return 0;
}

int GLRenderer::AddInstancedShader(uint64_t shader)
{
	ShaderProgram prog;
	prog = _shaderMgr->GetProgram(shader);
	if (prog.glProgram == -1)
		return -1;

	ShaderInstance inst;
	inst.glProgram = prog.glProgram;
	inst.renderDefs = new Array<ModelRenderDef>(*_alloc);

	hash::set(_instanceRenders, shader, inst);

	return 0;
}