# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(FreeZoneSimulation VERSION 1.0)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
endif()

# Source files
set(SOURCES
    main.cpp
    CellGenerator.cpp
    Board.cpp
    Statistics.cpp
    Experiment.cpp
)

# Header files (for IDE support)
set(HEADERS
    CellGenerator.h
    Board.h
    Statistics.h
    Experiment.h
)

# Create executable
add_executable(simulation ${SOURCES} ${HEADERS})

# Set output directory
set_target_properties(simulation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
