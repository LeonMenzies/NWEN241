cmake_minimum_required(VERSION 3.17)
project(NWEN241_Assignment1 C)

set(CMAKE_C_STANDARD 11)

include_directories(files)

add_executable(NWEN241_Assignment1
        files/editor.c
        files/editor.h
        files/t1test.c
        files/t2test.c
        files/t3test.c
        files/t3test_new.c
        files/t4test.c)
