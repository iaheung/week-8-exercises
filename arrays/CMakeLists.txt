cmake_minimum_required(VERSION 3.13)
project(arrays)
set(CMAKE_CXX_STANDARD 17)

add_executable(array_reduction array_reductions.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(array_reduction PUBLIC OpenMP::OpenMP_CXX)
endif()
