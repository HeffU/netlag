###########################################################
# Main CMake file for netlag
#
cmake_minimum_required (VERSION 2.8)

project (netlag)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
add_executable(NetLag "netlag/src/netlag.cpp")

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

# GLEW
find_library(lib_glew NAMES "glew32s"
	PATHS ${GLEW_LIBRARY_DIR} NO_DEFAULT_PATH)
add_definitions( -DGLEW_STATIC )
	
# GLFW
find_library(lib_glfw NAMES "glfw3"
	PATHS ${GLFW_LIBRARY_DIR} NO_DEFAULT_PATH)
	
# LuaJIT
find_library(lib_luajit NAMES "lua51"
	PATHS ${LUAJIT_LIBRARY_DIR} NO_DEFAULT_PATH)
	

target_link_libraries(NetLag
	${lib_glew} 
	${lib_glfw} 
	${lib_luajit})

###########################################################
# Preprocessor Definitions
#

set(_definitions 
	GLEW_STATIC
)

set_target_properties(NetLag PROPERTIES
	COMPILE_DEFINITIONS "${_definitions}")
	
