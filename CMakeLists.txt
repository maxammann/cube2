cmake_minimum_required(VERSION 3.0.2)
project(cube2)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)


add_subdirectory(matrix)
add_subdirectory(cube)