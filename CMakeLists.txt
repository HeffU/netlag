###########################################################
# Main CMake file for netlag
#
cmake_minimum_required (VERSION 2.8)

project (netlag)

###########################################################
# Third party dependencies
#

# GLEW
set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include 
	CACHE PATH "GLEW include files path" )
set(GLEW_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib/Release/Win32
	CACHE PATH "GLEW library files path" )

# LuaJIT


# GLFW
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include 
	CACHE PATH "GLFW include files path" )
set(GLFW_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib-msvc120
	CACHE PATH "GLFW library files path" )