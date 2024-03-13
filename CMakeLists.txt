cmake_minimum_required(VERSION 3.27)
project(CalculatorAads)

set(CMAKE_CXX_STANDARD 23)


include_directories(DataStructures/include
        googletest/googletest/include
        googletest/googlemock/include)

set(TEST_SOURCES
        tests_main.cpp
        DataStructures/tests/ListTest.cpp
        DataStructures/tests/StackTest.cpp
        DataStructures/tests/QueueTest.cpp)

add_executable(CalculatorAads main.cpp
        DataStructures/include/List.h)

add_subdirectory(googletest)
link_libraries(gmock)

add_executable(DataStructuresTests ${TEST_SOURCES})
