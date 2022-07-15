cmake_minimum_required(VERSION 3.10)

project(heartbeat_test C)

add_subdirectory(../../../unity unity)

set(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(INCLUDE_DIRS
	../../src
)

set(TEST_INCLUDE_DIRS
	../../..
)

set(SRCS
	../../src/heartbeat.c
)

set(TEST_SRCS
    heartbeat_test_main.c
    heartbeat_test_runner.c
    heartbeat_test.c
)

set(GLOBAL_DEFINES

)

include_directories(${INCLUDE_DIRS} ${TEST_INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

link_libraries(unity)
add_executable(${PROJECT_NAME} ${SRCS} ${TEST_SRCS})
