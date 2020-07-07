cmake_minimum_required(VERSION 3.16)

set(This Sitzen_zie_dupen-TESTS)

set(Sources
    DeployerTests.cpp
    some_tests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This}
    gtest_main
    Sitzen_zie_dupen
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
