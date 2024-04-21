cmake_minimum_required(VERSION 3.27)

project(abb)

add_executable(abb
    src/main.c
    src/abb.c)

target_include_directories(abb PRIVATE include)