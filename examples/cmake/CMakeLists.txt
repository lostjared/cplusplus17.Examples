cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(test01 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQURIED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cmake-test test.cpp)
