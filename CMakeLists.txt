cmake_minimum_required(VERSION 3.16)

set(This Genetic-deployer)
set(LIB_DIR libs)
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(${LIB_DIR}/googletest ${LIB_DIR}/googlemock)

SET(HEADERS
    include/Chromosome.hpp
    include/DataHolder.hpp
    include/FileReader.hpp
    include/GeneticDeployer.hpp
    include/DataStructures.hpp

    include/helpers/RandomNumberGenerator.hpp
)
set(SOURCES
    src/Chromosome.cpp
    src/DataHolder.cpp
    src/FileReader.cpp
    src/GeneticDeployer.cpp
)

add_library(${This} STATIC ${HEADERS} ${SOURCES})

add_subdirectory(tests)
