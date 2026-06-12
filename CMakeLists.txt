cmake_minimum_required(VERSION 4.1)
project(ikm2)

set(CMAKE_CXX_STANDARD 20)

add_executable(ikm2 main.cpp
        ball_list.cpp
        ball_list.h)
