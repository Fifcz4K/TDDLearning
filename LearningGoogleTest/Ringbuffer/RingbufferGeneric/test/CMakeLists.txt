cmake_minimum_required(VERSION 3.22)

set(This RingbufferGenericTests)

set(Sources
    RingbufferGenericTests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    RingbufferGeneric
)

add_test(
    NAME ${This}
    COMMAND ${This}
)