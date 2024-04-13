cmake_minimum_required(VERSION 3.7)

project(heap)

add_executable(heap
    src/heap.c
    src/main.c)

target_include_directories(heap PRIVATE include)