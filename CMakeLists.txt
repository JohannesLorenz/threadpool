cmake_minimum_required(VERSION 2.8)
include(cmake/init_project.txt)

# settings
project(threadpool)
set(DESCRIPTION "a simple C++ threadpool library")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "8")
SET(VERSION_PATCH "0")

# options
option(USE_MLOCK "provide the mlock system call" ON)

# libraries
MESSAGE("Checking for libraries...")
find_package(Threads) # = pthreads, for std::thread
list(APPEND THREAD_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

# custom targets
add_custom_target(stoat_threadpool stoat -c
	-w /usr/local/share/stoat/whitelist.txt
	-b /usr/local/share/stoat/blacklist.txt
	-w ${CMAKE_CURRENT_SOURCE_DIR}/data/stoat_suppression_list.txt
	-r ${CMAKE_CURRENT_BINARY_DIR}/src/)

# processing
include(cmake/process_project.txt)
print_summary_base()

