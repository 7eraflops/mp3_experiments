# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(mp3_learning_project)

# Set the C++ standard (C++11, C++17, etc.)
set(CMAKE_CXX_STANDARD 11)

# Include directories (add your include directory)
include_directories(include)

# Add the executable and source files
add_executable(mp3_learning.out
    src/main.cpp
    src/id3_tag_handler.cpp
    src/mp3_reader.cpp
)

# Optional: Add extra flags (if needed)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
