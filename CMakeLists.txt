cmake_minimum_required(VERSION 3.19)

set(This Genetic-deployer)
set(LIB_DIR libs)
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
######################################
###         CONFIGURE GTEST        ### 
######################################
#enable_testing()



# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                    EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets
# carry header search path
# dependencies automatically when
# using CMake 2.8.11 or
# later. Otherwise we have to add
# them here ourselves.
#if (CMAKE_VERSION VERSION_LESS 2.8.11)
#    include_directories("${gtest_SOURCE_DIR}/include")
#endif()
#add_subdirectory(${LIB_DIR}/googletest ${LIB_DIR}/googlemock)

SET(HEADERS
    include/Chromosome.hpp
    include/DataHolder.hpp
    include/FileExporter.hpp
    include/FileReader.hpp
    include/GeneticDeployer.hpp
    include/DataStructures.hpp

    include/helpers/Printers.hpp
    include/helpers/RandomNumberGenerator.hpp
)
set(SOURCES
    src/Chromosome.cpp
    src/DataHolder.cpp
    src/FileExporter.cpp
    src/FileReader.cpp
    src/GeneticDeployer.cpp
)

add_library(${This} STATIC ${HEADERS} ${SOURCES})

add_subdirectory(tests)
