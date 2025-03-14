cmake_minimum_required(VERSION 3.13)
project(pi)
set(CMAKE_CXX_STANDARD 17)

add_executable(pi main.cpp)
add_executable(test test.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(pi PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(test PUBLIC OpenMP::OpenMP_CXX)
endif()
