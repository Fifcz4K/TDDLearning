cmake_minimum_required(VERSION 3.22)

set(This RingbufferBasic)

set(Headers
    RingbufferBasic.h
)

set(Sources
    RingbufferBasic.c
)

add_subdirectory(test)

add_library(${This} STATIC ${Sources} ${Headers})