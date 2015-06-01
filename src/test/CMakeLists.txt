set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")
set(incl_dir "${src_dir}/../lib")

include_directories("${incl_dir}")

# TODO: comfortable function for that
#add_executable(test_seq test_seq.cpp)
#target_link_libraries(test_seq ringbuffer)

add_executable(test_tp test.cpp)
target_link_libraries(test_tp ${THREAD_LIBRARIES} ${AUDIO_LIBRARIES} threadpool)

add_executable(test_tp2 test2.cpp)
target_link_libraries(test_tp2 ${THREAD_LIBRARIES} ${AUDIO_LIBRARIES} threadpool)

#add_test(sequential test_seq)
add_test(threadpool test_tp)
add_test(threadpool2 test_tp2)
