cmake_minimum_required(VERSION 3.28.3)

project(hash)

add_executable(hash
    src/main.c
    src/hash.c)

target_include_directories(hash PRIVATE include)