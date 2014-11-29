
set(FOUNDATION_FILES
	"types.h"
	"collection_types.h"
	"memory_types.h"
	"math_types.h"
	"array.h"
	"hash.h"
	"queue.h"
	"memory.h"
	"memory.cpp"
	"murmur_hash.h"
	"murmur_hash.cpp"
	"string_stream.h"
	"string_stream.cpp"
	"snprintf_msvc.h"
	"temp_allocator.h"
)

add_sources(${FOUNDATION_FILES})