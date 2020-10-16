cmake_minimum_required(VERSION 3.17)
project(data_structures C)

set(CMAKE_C_STANDARD 11)

add_library(dc_dlist linked_list/dlinked_list.h linked_list/dlinked_list.c)

add_executable(test_dlink linked_list/test_dlink.c linked_list/dlinked_list.h linked_list/dlinked_list.c)