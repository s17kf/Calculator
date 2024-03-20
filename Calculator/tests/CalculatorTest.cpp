//
// Created by stefan on 18/03/24.
//

#include "gtest/gtest.h"
#include <sstream>

#include "Calculator.h"
#include "InputReader.h"
#include "LoggerStub.h"

using calculator::Calculator;
using calculator::InputReader;
using calculator::Result;
using input_output::LoggerStub;

class CalculatorTest : public ::testing::Test {
protected:
    std::stringstream inputStream;
    LoggerStub loggerStub;
    std::unique_ptr<InputReader> inputReader;
    std::unique_ptr<Calculator> calculator;

    void SetUp() override {
        inputReader = std::make_unique<InputReader>(inputStream);
        calculator = std::make_unique<Calculator>(*inputReader, loggerStub);
    }

    void TearDown() override {
        inputReader.reset();
        calculator.reset();
        loggerStub.reset();
    }
};

TEST_F(CalculatorTest, calculationGivesProperResults) {
    const std::string inputExpression =
            "MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) .";
    inputStream.str(inputExpression);
    const std::string expectedOutput =
            "100  1  34  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6\n"
            "MAX3 2 34 1 100\n"
            "MIN4 77 35 36 66 80 34 100\n"
            "MIN6 60 50 35 80 34 100\n";

    auto result = calculator->calculate();
    ASSERT_EQ(Result::Status::success, result.status);
    ASSERT_EQ(34, result.value);
    ASSERT_EQ(expectedOutput, loggerStub.str());
}

TEST_F(CalculatorTest, calculationGivesProperResults2) {
    const std::string inputExpression =
            "2 + MIN ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3 .";
    inputStream.str(inputExpression);
    const std::string expectedOutput =
            "2  100  1  6  5  *  2  +  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6  3  *  +\n"
            "* 5 6 1 100 2\n"
            "+ 2 30 1 100 2\n"
            "MAX3 2 32 1 100 2\n"
            "MIN4 77 35 36 66 80 32 100 2\n"
            "MIN6 60 50 35 80 32 100 2\n"
            "* 3 32 2\n"
            "+ 96 2\n";

    auto result = calculator->calculate();
    ASSERT_EQ(Result::Status::success, result.status);
    ASSERT_EQ(98, result.value);
    ASSERT_EQ(expectedOutput, loggerStub.str());
}

TEST_F(CalculatorTest, calculationGivesProperResults3) {
    const std::string inputExpression =
            "N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .";
    inputStream.str(inputExpression);
    const std::string expectedOutput =
            "400  N  11  3  2  *  -  2  /  +  200  N  N  +\n"
            "N 400\n"
            "* 2 3 11 -400\n"
            "- 6 11 -400\n"
            "/ 2 5 -400\n"
            "+ 2 -400\n"
            "N 200 -398\n"
            "N -200 -398\n"
            "+ 200 -398\n";

    auto result = calculator->calculate();
    ASSERT_EQ(Result::Status::success, result.status);
    ASSERT_EQ(-198, result.value);
    ASSERT_EQ(expectedOutput, loggerStub.str());
}

TEST_F(CalculatorTest, calculationGivesProperResults4) {
    const std::string inputExpression =
            "IF ( ( 6 + 8 ) , ( 4 / 2 ) , MIN ( 8 , 2 , 1 , 0 , 3 ) ) * 2 * 6 / N ( 3 ) .";
    inputStream.str(inputExpression);
    const std::string expectedOutput =
            "6  8  +  4  2  /  8  2  1  0  3  MIN5  IF  2  *  6  *  3  N  /\n"
            "+ 8 6\n"
            "/ 2 4 14\n"
            "MIN5 3 0 1 2 8 2 14\n"
            "IF 0 2 14\n"
            "* 2 2\n"
            "* 6 4\n"
            "N 3 24\n"
            "/ -3 24\n";

    auto result = calculator->calculate();
    ASSERT_EQ(Result::Status::success, result.status);
    ASSERT_EQ(-8, result.value);
    ASSERT_EQ(expectedOutput, loggerStub.str());
}

TEST_F(CalculatorTest, calculationThrowsDivisionByZero) {
    const std::string inputExpression =
            "MIN ( MIN ( IF ( 0 , 8 , 2 ) ) , MAX ( MIN ( 9 ) , 4 + 9 ) , ( IF ( 3 , 9 , 9 ) / "
            "MIN ( 7 , 0 , 6 , 2 , 1 ) ) , N ( 3 + 4 ) , 1 * 1 + IF ( 1 , 9 , 2 ) ) .";
    inputStream.str(inputExpression);
    const std::string expectedOutput =
            "0  8  2  IF  MIN1  9  MIN1  4  9  +  MAX2  3  9  9  IF  7  0  6  2  1  MIN5  /  3  "
            "4  +  N  1  1  *  1  9  2  IF  +  MIN5\n"
            "IF 2 8 0\n"
            "MIN1 2\n"
            "MIN1 9 2\n"
            "+ 9 4 9 2\n"
            "MAX2 13 9 2\n"
            "IF 9 9 3 13 2\n"
            "MIN5 1 2 6 0 7 9 13 2\n"
            "/ 0 9 13 2\n";

//    ASSERT_THROW(calculator->calculate(), std::overflow_error);
    auto result = calculator->calculate();
    ASSERT_EQ(Result::Status::error, result.status);

    ASSERT_EQ(expectedOutput, loggerStub.str());
}