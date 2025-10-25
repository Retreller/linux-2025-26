project(IteratorDemos)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/util/iterator)

add_executable(filter_integer_iterator demo/iterator/filter_integer_iterator.cpp)
add_executable(reverse_array_iterator demo/iterator/reverse_array_iterator.cpp)
add_executable(circular_int_iterator demo/iterator/circular_int_iterator.cpp)
