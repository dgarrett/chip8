cmake_minimum_required(VERSION 3.15)

project(chip8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Freetype REQUIRED)
find_package(SDL2 REQUIRED)

add_subdirectory(lib)
add_subdirectory(src)