cmake_minimum_required(VERSION 3.22)

set(This LowBatteryAlarm)

set(Headers
    LowBatteryAlarm.h
)

set(Sources
    LowBatteryAlarm.c
)

add_subdirectory(test)

add_library(${This} STATIC ${Sources} ${Headers})