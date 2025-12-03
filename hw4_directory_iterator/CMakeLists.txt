project(directory_iterator)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/util/iterator)

add_executable(directory_iterator demo/iterator/directory_iterator_demo.cpp)