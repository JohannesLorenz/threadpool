set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB lib_src ${src_dir}/*.cpp)
file(GLOB lib_hdr ${src_dir}../include/*.h)

add_library(threadpool SHARED ${lib_src} ${lib_hdr})


