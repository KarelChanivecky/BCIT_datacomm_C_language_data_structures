cmake_minimum_required(VERSION 3.17)
project(dc_data_structures C)

set(CMAKE_C_STANDARD 11)

add_library(dc_utils SHARED ../lib/dlinked_list.h ../lib/dlinked_list.c ../lib/bit_array.c ../lib/bit_array.h
        ../lib/dc_tree.h ../lib/dc_tree.c ../lib/dc_threaded_queue.c ../lib/dc_threaded_queue.h)

target_compile_options(dc_utils PRIVATE -Wpedantic -Wall -Wextra -fPIC)

add_executable(test_dlinked_list test_dlink.c)
target_link_libraries(test_dlinked_list dc_utils)

add_executable(test_bit_array test_bit_array.c )
target_link_libraries(test_bit_array dc_utils)

add_executable(test_dc_threaded_queue test_dc_threaded_queue.c)
target_link_libraries(test_dc_threaded_queue dc_utils pthread)