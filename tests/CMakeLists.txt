cmake_minimum_required(VERSION 3.16)

set(This Genetic-deployer-TESTS)

set(Sources
    ChromosomeTests.cpp
    DeployerTests.cpp
    PerformanceTests.cpp

    PerformanceParameters.hpp
    matchers/ChromosomeMatcher.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This}
    gtest_main
    gmock_main
    Genetic-deployer
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
