cmake_minimum_required(VERSION 3.27)

project(avl)

add_executable(avl
    src/avl.c
    src/main.c)

target_include_directories(avl PRIVATE include)