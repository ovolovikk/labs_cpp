cmake_minimum_required(VERSION 3.16)
project(AnyOfStudy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(any_of_no_opt main.cpp)
target_compile_options(any_of_no_opt PRIVATE -O0)
target_compile_definitions(any_of_no_opt PRIVATE NDEBUG)
target_link_libraries(any_of_no_opt PRIVATE Threads::Threads)

add_executable(any_of_max_opt main.cpp)
target_compile_options(any_of_max_opt PRIVATE -O3)
target_compile_definitions(any_of_max_opt PRIVATE NDEBUG)
target_link_libraries(any_of_max_opt PRIVATE Threads::Threads)