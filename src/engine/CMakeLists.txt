
set(ENGINE_FILES
	"engine.cpp"
	"engine.h"
)

add_subdirectory(rendering)
add_subdirectory(scripting)
add_sources(${ENGINE_FILES})