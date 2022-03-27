cmake_minimum_required(VERSION 3.22)

set(This TDDLearning)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)
# add_subdirectory(Ringbuffer)
add_subdirectory(Communication)