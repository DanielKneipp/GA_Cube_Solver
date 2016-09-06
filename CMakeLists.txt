cmake_minimum_required(VERSION 3.0.2)
project(GA_Cube_Solver)

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_INSTALL_PREFIX "../deploy")

add_subdirectory(cube)
add_subdirectory(ga)
add_subdirectory(test)
