# Main CMake file for netlag
cmake_minimum_required (VERSION 2.8)


project (netlag)

###########################################################
# Third party dependencies
#

# GLEW
add_definitions(-DGLEW_STATIC)
add_subdirectory(libraries/glew)