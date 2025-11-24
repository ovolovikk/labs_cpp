cmake_minimum_required(VERSION 3.10)

project(Lab5Variant3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab5Variant3 main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(Lab5Variant3 PRIVATE Threads::Threads)
