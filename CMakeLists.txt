cmake_minimum_required(VERSION 3.16)

project(gamera
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gamera
    src/main.cpp
    src/machine/cpu.cpp
    src/machine/memory.cpp
    src/machine/decoder.cpp
)