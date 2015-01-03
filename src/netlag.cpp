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
*	netlag.cpp - Entry point and bootstrapping
**********************************************************************/

#include "engine\engine.h"
using namespace netlag;

#ifdef PLATFORM_OS_WIN
//int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
// Use the above once the project has its own logging / console. Switch subsystem to Win32 only.
int main(int argc, char ** argv)
#else
int main(int argc, char ** argv)
#endif
{
	Engine* engine = new Engine();
	engine->Initialize();
	engine->Run();
	engine->Cleanup();
	delete engine;

	return 0;
}