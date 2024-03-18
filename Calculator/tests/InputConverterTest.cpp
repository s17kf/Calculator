//
// Created by stefan on 14/03/24.
//
#include "gtest/gtest.h"
#include <vector>
#include "sstream"

#include "InputConverter.h"
#include "InputReader.h"
#include "Symbol.h"

#include "List.h"

using calculator::InputConverter;
using calculator::InputReader;
using calculator::Symbol;
using calculator::TokenType;

using calculator::Operation;
using calculator::Function;
using calculator::Bracket;


class InputConverterTest : public ::testing::Test {
protected:
};

TEST_F(InputConverterTest, convertingFormula) {
    const std::string inputExpression =
            "2 + MIN ( 100 , MAX ( 1 , 6 / 5 + 2 , 2 ) , N 80 ,  MIN ( 66  , 36, 35 , 77 ) , 50 , 60 ) * 3 .";
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
                    .token = {.function={.type=Function::Type::max}}},
            {.tokenType = TokenType::number,
                    .token = {.number=80}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::negation}}},
            {.tokenType = TokenType::number,
                    .token = {.number=66}},
            {.tokenType = TokenType::number,
                    .token = {.number=36}},
            {.tokenType = TokenType::number,
                    .token = {.number=35}},
            {.tokenType = TokenType::number,
                    .token = {.number=77}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::min}}},
            {.tokenType = TokenType::number,
                    .token = {.number=50}},
            {.tokenType = TokenType::number,
                    .token = {.number=60}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::min}}},
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
    uint readSymbols = 0;
    while (inputConverter.symbolsLeft()) {
        Symbol *symbol = inputConverter.removeNextSymbol();
        ASSERT_EQ(expectedSymbols[readSymbols], *symbol);
        delete symbol;
        ++readSymbols;
    }
    ASSERT_EQ(expectedSymbols.size(), readSymbols);
}