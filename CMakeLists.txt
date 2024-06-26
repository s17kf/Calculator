cmake_minimum_required(VERSION 3.27)
project(CalculatorAads)

set(CMAKE_CXX_STANDARD 23)


include_directories(
        DataStructures/include
        Calculator/include
        InputOutput/include
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
        InputOutput/src/LoggerStub.cpp
        InputOutput/src/UserInputReaderStub.cpp
)

set(MAIN_SOURCES
        Calculator/src/Calculator.cpp
        Calculator/src/InputConverter.cpp
        Calculator/src/InputReader.cpp
        Calculator/src/Symbol.cpp
        DataStructures/src/String.cpp
        InputOutput/src/ConsoleLogger.cpp
        InputOutput/src/UserInputReaderImpl.cpp
)

add_executable(CalculatorAads main.cpp ${MAIN_SOURCES})

add_subdirectory(googletest)

add_executable(DataStructuresTests ${DATA_STRUCTURES_TEST_SOURCES})
add_executable(CalculatorTests ${CALCULATOR_TEST_SOURCES})
target_link_libraries(DataStructuresTests gmock)
target_link_libraries(CalculatorTests gmock)
