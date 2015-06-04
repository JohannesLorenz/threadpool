configure_file("${CMAKE_CURRENT_SOURCE_DIR}/threadpool.pc.in"
	"${CMAKE_CURRENT_BINARY_DIR}/threadpool.pc" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/threadpool.pc"
	DESTINATION "${INSTALL_LIB_DIR}/pkgconfig")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/version.h"
		"${CMAKE_CURRENT_BINARY_DIR}/config.h"
		DESTINATION "${INSTALL_INC_DIR}/ringbuffer")
# ^ TODO: into common files

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(test)

