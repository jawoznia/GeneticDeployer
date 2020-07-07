cmake_minimum_required(VERSION 3.16)

set(This Sitzen_zie_dupen)
set(LIB_DIR libs)
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(${LIB_DIR}/googletest)

SET(HEADERS
    calc.hpp
    hello.hpp
)
set(SOURCES
    hello.cpp
)

add_library(${This} STATIC ${SOURCES} ${HEADERS})

add_subdirectory(tests)
