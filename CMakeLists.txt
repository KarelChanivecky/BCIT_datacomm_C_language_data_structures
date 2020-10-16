cmake_minimum_required(VERSION 3.17)
project(data_structures C)

set(CMAKE_C_STANDARD 11)

add_library(dc_dlinked_list lib/dlinked_list.h lib/dlinked_list.c)

add_library(dc_bit_array lib/bit_array.c lib/bit_array.h)