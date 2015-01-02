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
*	platform.h - Information and setup for specific platforms
**********************************************************************/
#pragma once

// Platform detection
#if (defined(WIN32)) // The project target is currently only 32bit.
#define PLATFORM_OS_WIN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif (defined(__APPLE__))
#define PLATFORM_OS_OSX
#else // Any other target is presumed to be linux/unix for now.
#define PLATFORM_OS_LINUX
#endif


// GLFW definitions for exposing native window handles for OVR
#if defined(PLATFORM_OS_WIN)
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#elif defined(PLATFORM_OS_OSX)
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#elif defined(PLATFORM_OS_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#endif


