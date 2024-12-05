cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

set(JIT_LIB_NAME JIT_LIB)

set(JIT_SRC
    value.cpp
    ir_graph.cpp
    instr.cpp
    bb.cpp
)

add_library(${JIT_LIB_NAME} STATIC ${JIT_SRC})
target_include_directories(${JIT_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(MAIN main.cpp)
target_link_libraries(MAIN PUBLIC JIT_LIB)