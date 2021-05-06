cmake_minimum_required(VERSION 3.19)
project(indic C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(indic main.c)

target_link_libraries(indic ${SDL2_LIBRARIES})
include_directories(./lib)