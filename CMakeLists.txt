cmake_minimum_required(VERSION 3.15)
project(Genetic_deployer)

set(CMAKE_CXX_STANDARD 20)
set(Boost_INCLUDE_DIR /usr/include/boost)

find_package(Boost REQUIRED COMPONENTS)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCES
        # cpp
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/src/FileReader.cpp
        ${PROJECT_SOURCE_DIR}/src/GeneticDeployer.cpp
        ${PROJECT_SOURCE_DIR}/src/DataHolder.cpp include/DataStructures.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include/
)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
