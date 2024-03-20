cmake_minimum_required(VERSION 3.27)
project(CalculatorAads)

set(CMAKE_CXX_STANDARD 23)


include_directories(
        DataStructures/include
        Calculator/include
        googletest/googletest/include
        googletest/googlemock/include)

set(DATA_STRUCTURES_TEST_SOURCES
        tests_main.cpp
        DataStructures/src/String.cpp
        DataStructures/tests/ListTest.cpp
        DataStructures/tests/StackTest.cpp
        DataStructures/tests/QueueTest.cpp
        DataStructures/tests/StringTest.cpp
)

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
        DataStructures/src/String.cpp
)

set(MAIN_SOURCES
        main.cpp
        Calculator/src/Calculator.cpp
        Calculator/src/InputConverter.cpp
        Calculator/src/InputReader.cpp
        Calculator/src/Symbol.cpp
        DataStructures/src/String.cpp
)

add_executable(CalculatorAads ${MAIN_SOURCES})

add_subdirectory(googletest)
link_libraries(gmock)

add_executable(DataStructuresTests ${DATA_STRUCTURES_TEST_SOURCES})
add_executable(CalculatorTests ${CALCULATOR_TEST_SOURCES})
