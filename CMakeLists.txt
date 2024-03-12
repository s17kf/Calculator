cmake_minimum_required(VERSION 3.28)
project(CalculatorAads)

set(CMAKE_CXX_STANDARD 23)


include_directories(DataStructures/include
        googletest/googletest/include
        googletest/googlemock/include)

set(TEST_SOURCES
        DataStructures/tests/ListTest.cpp
        tests_main.cpp)

add_subdirectory(googletest)
link_libraries(gmock)

add_executable(CalculatorAads main.cpp
        DataStructures/include/List.h)

add_executable(DataStructuresTests ${TEST_SOURCES})
