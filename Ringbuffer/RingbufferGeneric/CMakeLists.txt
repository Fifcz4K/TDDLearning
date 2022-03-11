cmake_minimum_required(VERSION 3.22)

set(This RingbufferGeneric)

set(Headers
    RingbufferGeneric.h
)

set(Sources
    RingbufferGeneric.c
)

add_subdirectory(test)

add_library(${This} STATIC ${Sources} ${Headers})