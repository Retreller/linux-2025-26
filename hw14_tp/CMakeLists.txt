project(ThreadPool)

add_executable(tp_demo demo/main.cpp util/thread/thread_pool.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/util/thread)
