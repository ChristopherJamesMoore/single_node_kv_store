cmake_minimum_required(VERSION 3.16)
project(kvstore)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(kvstore src/main.cpp src/store.cpp)
