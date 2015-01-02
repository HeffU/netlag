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
*	engine.cpp - Engine class implementation
**********************************************************************/

#include "engine.h"
#include "memory.h"

// For temp tests:
#include "array.h"
#include "murmur_hash.h"

using namespace netlag;

Engine::Engine()
{
	if (!glfwInit()) { // TODO: log / output errors.
		exit(EXIT_FAILURE);
	}
}

Engine::~Engine()
{
	glfwTerminate();
}

int Engine::Initialize()
{
	// Initialize memory allocators
	foundation::memory_globals::init();
	_mainAlloc = &foundation::memory_globals::default_allocator();

	// Initialize asset loading
	_assetMgr = new AssetManager(_mainAlloc);

	// Initialize scripting
	_scriptMgr = new ScriptManager(_mainAlloc, _assetMgr);

	// Initialize the window
	glfwWindowHint(GLFW_DEPTH_BITS, 16);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef PLATFORM_OS_OSX
	// Quick fix for Mac
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	_window = glfwCreateWindow(640, 480, "netlag", NULL, NULL);
	if (!_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(_window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return EXIT_FAILURE;
	}

	return 0;
}

int Engine::Run()
{
	// Temp tests.
	char* path = "test.lua";
	foundation::Array<char*> list(*_mainAlloc);
	foundation::array::push_back(list, path);
	_assetMgr->LoadFileList(list);
	uint64_t handle = foundation::murmur_hash_64
		(path, sizeof("test.lua")-1, 0);
	_scriptMgr->RunScript(handle);
	//_scriptMgr->RunString("print('Scriptmanager Initializing..');");

	while (!_scriptMgr->StateAvailable(0));

	_assetMgr->UnloadFileList(list);
	foundation::array::clear(list);



	/******************************************/

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	float points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

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

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	// Main running loop:
	while (!glfwWindowShouldClose(_window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	return 0;
}

int Engine::Cleanup()
{
	// Dirty trick here could be letting the OS handle all allocated memory.
	// Makes for a quicker shutdown but should it be used?

	// Probably ought to migrate all memory allocations to custom allocs
	// new / delete in the meantime for classes, malloc for PODs

	glfwDestroyWindow(_window);

	delete _assetMgr;
	delete _scriptMgr;

	foundation::memory_globals::shutdown();

	return 0;
}