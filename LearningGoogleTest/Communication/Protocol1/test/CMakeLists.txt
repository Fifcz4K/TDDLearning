cmake_minimum_required(VERSION 3.22)

set(This Protocol1Tests)

set(Sources
    Protocol1Tests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    Protocol1
)

add_test(
    NAME ${This}
    COMMAND ${This}
)