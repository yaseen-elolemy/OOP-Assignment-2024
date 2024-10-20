cmake_minimum_required(VERSION 3.27)

set(This TASK2)

project(${This} C CXX)

set(CMAKE_CXX_STANDARD 17)


enable_testing()

add_subdirectory(googletest)

set(Source
        main.cpp
        Polynomial.cpp
)


add_executable(${This} ${Source})

target_link_libraries(${This} gtest gtest_main)


add_test(
        NAME ${This}
        COMMAND ${This}
)