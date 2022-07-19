cmake_minimum_required(VERSION 3.22)

project(TEST_TENNIS)

add_executable(${PROJECT_NAME} test_main.cpp test_tennis.cpp)

add_subdirectory(../src src)
include_directories(../src)
target_link_libraries(${PROJECT_NAME} tennis)