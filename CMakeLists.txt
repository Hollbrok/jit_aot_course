cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(jit_course LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wundef -Wwrite-strings -Wcast-qual -Wlogical-op")

set(COMPILE_OPTIONS
	-Wall
	-Wconversion
	-Wextra
	-Wwrite-strings
	-Wcast-qual
	-Wundef
	-Wlogical-op
)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(${COMPILE_OPTIONS})

add_subdirectory(src)

