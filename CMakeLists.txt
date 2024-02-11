cmake_minimum_required(VERSION 3.27)
project(mallocx)

set(CMAKE_CXX_STANDARD 23)

add_executable(mallocx main.cpp malloc.cpp malloc.hpp)
