cmake_minimum_required(VERSION 3.22)

set(This RingbufferBasicTests)

set(Sources
    RingbufferBasicTests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    RingbufferBasic
)

add_test(
    NAME ${This}
    COMMAND ${This}
)