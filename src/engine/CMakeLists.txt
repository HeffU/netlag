
set(ENGINE_FILES
	"engine.cpp"
	"engine.h"
)

add_subdirectory(content)
add_subdirectory(rendering)
add_subdirectory(scripting)
add_subdirectory(utilities)
add_subdirectory(windowing)

add_sources(${ENGINE_FILES})