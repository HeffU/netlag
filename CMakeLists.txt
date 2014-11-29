###########################################################
# Main CMake file for netlag
#
cmake_minimum_required (VERSION 2.8)

project (netlag)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

###########################################################
# Source setup macro
#
macro(add_sources)
    file(RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach(_src ${ARGN})
        if(_relPath)
            list (APPEND NETLAG_SOURCE_FILES "${_relPath}/${_src} ")
        else()
            list (APPEND NETLAG_SOURCE_FILES "${_src} ")
        endif()
		# add directory structure information for the file
		string(REGEX REPLACE "/" "\\\\" _srcGrp ${_relPath})
		file (RELATIVE_PATH _projRelPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
		if ("${_src}" MATCHES ".*\\.cpp")
			set(_srcGrp "Source Files\\${_srcGrp}")
		elseif("${_src}" MATCHES ".*\\.h")
			set(_srcGrp "Header Files\\${_srcGrp}")
		endif()
		string(REGEX REPLACE "\\\\src" "" _srcGrp ${_srcGrp})
		message(${_srcGrp} " " ${_projRelPath}/${_src})
		list(APPEND NETLAG_SOURCE_GROUPS "${_srcGrp}")
		list(APPEND NETLAG_SOURCE_GROUP_PATHS "${_projRelPath}/${_src}")
    endforeach()
    if(_relPath)
        # propagate lists to parent directory
        set(NETLAG_SOURCE_FILES ${NETLAG_SOURCE_FILES} PARENT_SCOPE)
		set(NETLAG_SOURCE_GROUP_PATHS ${NETLAG_SOURCE_GROUP_PATHS} PARENT_SCOPE)
		set(NETLAG_SOURCE_GROUPS ${NETLAG_SOURCE_GROUPS} PARENT_SCOPE)
    endif()
endmacro()

###########################################################
# Source setup and target creation
#
add_subdirectory(src)
add_subdirectory(libs/foundation)
add_executable(NetLag ${NETLAG_SOURCE_FILES})


# use generated lists to create source groups
list(LENGTH NETLAG_SOURCE_GROUP_PATHS _len)
math(EXPR _len "${_len} - 1")
foreach(_index RANGE ${_len})
	list(GET NETLAG_SOURCE_GROUP_PATHS ${_index} _filePath)
	list(GET NETLAG_SOURCE_GROUPS ${_index} _fileGrp)
	source_group("${_fileGrp}" FILES "${_filePath}")
endforeach()

###########################################################
# Dependency folder setup
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
	
# LibOVR
set(OVR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/ovr/Include 
	CACHE PATH "Oculus SDK include files path" )
set(OVR_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/ovr/Lib/Win32/VS2013
	CACHE PATH "Oculus SDK library files path" )
	
###########################################################
# Include and linking setup
#

# GLEW
include_directories(${GLEW_INCLUDE_DIR})
# GLFW
include_directories(${GLFW_INCLUDE_DIR})
# LuaJIT
include_directories(${LUAJIT_INCLUDE_DIR})
# LibOVR
include_directories(${OVR_INCLUDE_DIR})


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
	
# LibOVR
find_library(lib_ovr NAMES "libovr"
	PATHS ${OVR_LIBRARY_DIR} NO_DEFAULT_PATH)
	
target_link_libraries(NetLag
	${lib_glew} 
	${lib_glfw} 
	${lib_luajit}
	${lib_ovr})

###########################################################
# Preprocessor Definitions
#

set(_definitions 
	GLEW_STATIC
)

set_target_properties(NetLag PROPERTIES
	COMPILE_DEFINITIONS "${_definitions}")
	
