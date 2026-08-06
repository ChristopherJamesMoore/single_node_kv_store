cmake_minimum_required(VERSION 3.16)
project(kvstore)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)

add_executable(kvstore src/main.cpp src/store.cpp)

add_executable(kvserver src/server.cpp src/store.cpp)
target_include_directories(kvserver PRIVATE third_party)
target_link_libraries(kvserver PRIVATE Threads::Threads)
