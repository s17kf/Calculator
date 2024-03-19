cmake_minimum_required(VERSION 3.27)
project(CalculatorAads)

set(CMAKE_CXX_STANDARD 23)


include_directories(
        DataStructures/include
        Calculator/include
        googletest/googletest/include
        googletest/googlemock/include)

set(TEST_SOURCES
        tests_main.cpp
        DataStructures/tests/ListTest.cpp
        DataStructures/tests/StackTest.cpp
        DataStructures/tests/QueueTest.cpp)

set(CALCULATOR_TEST_SOURCES
        tests_main.cpp
        Calculator/tests/SymbolTest.cpp
        Calculator/tests/InputReaderTest.cpp
        Calculator/tests/InputConverterTest.cpp
        Calculator/tests/CalculatorTest.cpp
        Calculator/src/Symbol.cpp
        Calculator/src/InputReader.cpp
        Calculator/src/InputConverter.cpp
        Calculator/src/Calculator.cpp
)

add_executable(CalculatorAads main.cpp
        Calculator/src/InputReader.cpp
        DataStructures/include/List.h)

add_subdirectory(googletest)
link_libraries(gmock)

add_executable(DataStructuresTests ${TEST_SOURCES})
add_executable(CalculatorTests ${CALCULATOR_TEST_SOURCES})
