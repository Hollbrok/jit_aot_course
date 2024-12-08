cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

set(JIT_LIB_NAME JIT_LIB)

set(JIT_SRC
    value.cpp
    ir_graph.cpp
    instr.cpp
    bb.cpp
    dsu.cpp
    dfo.cpp
    dom_tree_builder.cpp
)

add_library(${JIT_LIB_NAME} STATIC ${JIT_SRC})
target_include_directories(${JIT_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_executable(MAIN main.cpp)
target_link_libraries(MAIN PUBLIC JIT_LIB)

# TESTS

add_executable(test_dsu test_dsu.cpp)
target_link_libraries(test_dsu PUBLIC JIT_LIB)

add_executable(test_dfo test_dfo.cpp)
target_link_libraries(test_dfo PUBLIC JIT_LIB)

add_executable(test_dom_tree test_dom_tree.cpp)
target_link_libraries(test_dom_tree PUBLIC JIT_LIB)
