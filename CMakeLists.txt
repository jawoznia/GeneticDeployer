cmake_minimum_required(VERSION 3.15)
project(Genetic_deployer)

set(CMAKE_CXX_STANDARD 20)


set(SOURCES
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/src/FileReader.cpp
        ${PROJECT_SOURCE_DIR}/src/GeneticDeployer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include/
)
