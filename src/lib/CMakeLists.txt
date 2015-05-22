set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB lib_src ${src_dir}/*.cpp)
file(GLOB lib_hdr ${src_dir}/../include/*.h) # todo: special cmake file there?

add_library(threadpool SHARED ${lib_src} ${lib_hdr})
target_link_libraries(threadpool ${THREAD_LIBRARIES} ${AUDIO_LIBRARIES})

install(TARGETS threadpool
	LIBRARY DESTINATION ${INSTALL_LIB_DIR})
install(FILES ${lib_hdr}
	DESTINATION "${INSTALL_INC_DIR}/threadpool")
