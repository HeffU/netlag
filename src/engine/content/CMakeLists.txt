
set(CONTENT_FILES
	"assetmanager.cpp"
	"assetmanager.h"
	"asset_types.h"
	"asset_loaders.h"
)

add_subdirectory(loaders)

add_sources(${CONTENT_FILES})