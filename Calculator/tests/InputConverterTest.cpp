//
// Created by stefan on 14/03/24.
//
#include "gtest/gtest.h"
#include <vector>
#include <sstream>

#include "InputConverter.h"
#include "InputReader.h"
#include "Symbol.h"

using calculator::InputConverter;
using calculator::InputReader;
using calculator::Symbol;
using calculator::TokenType;

using calculator::Operation;
using calculator::Function;
using calculator::Bracket;


class InputConverterTest : public ::testing::Test {
protected:
    static void verifyFormula(InputConverter &inputConverter, const std::vector<Symbol> &expectedSymbols) {
        uint readSymbols = 0;
        while (inputConverter.symbolsLeft()) {
            Symbol *symbol = inputConverter.removeNextSymbol();
            ASSERT_EQ(expectedSymbols[readSymbols], *symbol) << "Wrong symbol at index: " << readSymbols;
            delete symbol;
            ++readSymbols;
        }
        ASSERT_EQ(expectedSymbols.size(), readSymbols);
    }
};

TEST_F(InputConverterTest, convertingFormula) {
    const std::string inputExpression =
            "2 + MIN ( 100 , MAX ( 1 , 6 / 5 + 2 , 2 ) , N 80 ,  IF ( 66  , 35 , 77 ) , 50 , 60 ) * 3 .";
    const std::vector<Symbol> expectedSymbols{
            {.tokenType = TokenType::number,
                    .token = {.number=2}},
            {.tokenType = TokenType::number,
                    .token = {.number=100}},
            {.tokenType = TokenType::number,
                    .token = {.number=1}},
            {.tokenType = TokenType::number,
                    .token = {.number=6}},
            {.tokenType = TokenType::number,
                    .token = {.number=5}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::division}}},
            {.tokenType = TokenType::number,
                    .token = {.number=2}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::addition}}},
            {.tokenType = TokenType::number,
                    .token = {.number=2}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::max,
                            .argc=3}}},
            {.tokenType = TokenType::number,
                    .token = {.number=80}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::negation,
                            .argc=1}}},
            {.tokenType = TokenType::number,
                    .token = {.number=66}},
            {.tokenType = TokenType::number,
                    .token = {.number=35}},
            {.tokenType = TokenType::number,
                    .token = {.number=77}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::condition,
                            .argc=3}}},
            {.tokenType = TokenType::number,
                    .token = {.number=50}},
            {.tokenType = TokenType::number,
                    .token = {.number=60}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::min,
                            .argc=6}}},
            {.tokenType = TokenType::number,
                    .token = {.number=3}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::multiplying}}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::addition}}},
    };

    std::stringstream inputStream(inputExpression);
    InputReader inputReader(inputStream);
    InputConverter inputConverter(inputReader);

    inputConverter.convertFormula();

    verifyFormula(inputConverter, expectedSymbols);
}

TEST_F(InputConverterTest, convertingFormula2) {
    const std::string inputExpression =
            "N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .";
    const std::vector<Symbol> expectedSymbols{
            {.tokenType = TokenType::number,
                    .token = {.number=400}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::negation,
                            .argc=1}}},
            {.tokenType = TokenType::number,
                    .token = {.number=11}},
            {.tokenType = TokenType::number,
                    .token = {.number=3}},
            {.tokenType = TokenType::number,
                    .token = {.number=2}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::multiplying}}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::subtraction}}},
            {.tokenType = TokenType::number,
                    .token = {.number=2}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::division}}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::addition}}},
            {.tokenType = TokenType::number,
                    .token = {.number=200}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::negation,
                            .argc=1}}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::negation,
                            .argc=1}}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::addition}}},
    };

    std::stringstream inputStream(inputExpression);
    InputReader inputReader(inputStream);
    InputConverter inputConverter(inputReader);

    inputConverter.convertFormula();

    verifyFormula(inputConverter, expectedSymbols);
}