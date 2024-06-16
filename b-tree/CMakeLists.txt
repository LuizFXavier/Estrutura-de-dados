cmake_minimum_required(VERSION 3.27)

project(b_tree)

add_executable(b_tree
    src/b_tree.c
    src/main.c)

target_include_directories(b_tree PRIVATE include)