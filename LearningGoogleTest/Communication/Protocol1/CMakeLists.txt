cmake_minimum_required(VERSION 3.22)

set(This Protocol1)

set(Headers
    Protocol1.h
)

set(Sources
    Protocol1.c
)

add_subdirectory(test)

add_library(${This} STATIC ${Sources} ${Headers})