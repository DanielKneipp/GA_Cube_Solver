cmake_minimum_required(VERSION 3.1.0)
project(GA_Cube_Solver)

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_INSTALL_PREFIX "../deploy")

set (CMAKE_CXX_STANDARD 11)

add_subdirectory(cube)
add_subdirectory(ga)
add_subdirectory(test)
add_subdirectory(utils)
