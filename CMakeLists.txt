cmake_minimum_required(VERSION 3.22)
project(verlet_demo)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SDL EXCLUDE_FROM_ALL)

add_executable(verlet_demo WIN32 main.cpp vector.h renderer.cpp renderer.h)

target_link_libraries(verlet_demo SDL2-static SDL2main)
