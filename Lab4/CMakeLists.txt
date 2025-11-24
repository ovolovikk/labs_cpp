cmake_minimum_required(VERSION 3.10)

project(Lab4Variant2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

add_executable(Lab4Variant2 main.cpp)

target_link_libraries(Lab4Variant2 PRIVATE Threads::Threads)

message(STATUS "CMake configured for Lab4Variant2 (C++17)")