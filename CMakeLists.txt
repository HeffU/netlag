###########################################################
# Main CMake file for netlag
#
cmake_minimum_required (VERSION 2.8)

project (netlag)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

###########################################################
# Third party dependencies setup
#

# GLEW
set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include 
	CACHE PATH "GLEW include files path" )
set(GLEW_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib/Release/Win32
	CACHE PATH "GLEW library files path" )

# LuaJIT
set(LUAJIT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/luajit/src 
	CACHE PATH "LuaJIT include files path" )
set(LUAJIT_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/luajit/src 
	CACHE PATH "LuaJIT library files path" )
set(LUAJIT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/luajit/src 
	CACHE PATH "LuaJIT binary files path" )

# GLFW
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include 
	CACHE PATH "GLFW include files path" )
set(GLFW_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib-msvc120
	CACHE PATH "GLFW library files path" )
	
###########################################################
# Include and linking setup
#

# GLEW
include_directories(${GLEW_INCLUDE_DIR})
# GLFW
include_directories(${GLFW_INCLUDE_DIR})
# LuaJIT
include_directories(${LUAJIT_INCLUDE_DIR})

###########################################################
# Source/Header CMake files
#

add_subdirectory(netlag/src)

###########################################################
# Library linking
#
