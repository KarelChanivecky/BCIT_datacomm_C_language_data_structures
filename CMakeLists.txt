cmake_minimum_required(VERSION 3.17)
project(dc_data_structures C)

set(CMAKE_C_STANDARD 11)

add_library(dc_utils SHARED lib/dlinked_list.h lib/dlinked_list.c lib/bit_array.c lib/bit_array.h
            lib/dc_tree.h lib/dc_tree.c lib/dc_threaded_queue.c lib/dc_threaded_queue.h)
target_link_libraries(dc_utils pthread)
target_compile_options(dc_utils PRIVATE -Wpedantic -Wall -Wextra -fPIC)


install(TARGETS dc_utils DESTINATION lib)
install(FILES lib/bit_array.h lib/dlinked_list.h lib/dc_tree.h lib/dc_threaded_queue.h DESTINATION include/dc_utils)
