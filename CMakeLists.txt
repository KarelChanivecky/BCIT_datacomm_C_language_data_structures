cmake_minimum_required(VERSION 3.17)
project(data_structures C)

set(CMAKE_C_STANDARD 11)

add_library(dc_dlist lib/dlinked_list.h lib/dlinked_list.c)
