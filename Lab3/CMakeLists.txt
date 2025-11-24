cmake_minimum_required(VERSION 3.15)
project(ComputationSchema)

# Встановлюємо стандарт C++20 глобально для проекту
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_executable(prog main.cpp)