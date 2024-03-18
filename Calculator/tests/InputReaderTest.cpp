//
// Created by stefan on 14/03/24.
//

#include "gtest/gtest.h"
#include <list>
#include <sstream>
#include <ranges>

#include "InputReader.h"
#include "Symbol.h"

using calculator::InputReader;
using calculator::Symbol;
using calculator::TokenType;

using calculator::Operation;
using calculator::Function;
using calculator::Bracket;

class InputReaderTest : public ::testing::Test {
protected:
};

TEST_F(InputReaderTest, validMultiTypeInputTest) {
    const std::string inputExpression =
            "2 + MIN ( 100 , MAX ( 1 , 6 / 5 + 2 , 2 ) , N 80 ,  IF ( 66  , 35 , 77 ) , 50 , 60 ) * 3 .";

    const std::list<Symbol> expectedSymbols{
            {.tokenType = TokenType::number,
                    .token = {.number=2}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::addition}}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::min}}},
            {.tokenType = TokenType::bracket,
                    .token = {.bracket={.type=calculator::Bracket::Type::left}}},
            {.tokenType = TokenType::number,
                    .token = {.number=100}},
            {.tokenType = TokenType::comma,
                    .token = {.comma=','}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::max}}},
            {.tokenType = TokenType::bracket,
                    .token = {.bracket={.type=calculator::Bracket::Type::left}}},
            {.tokenType = TokenType::number,
                    .token = {.number=1}},
            {.tokenType = TokenType::comma,
                    .token = {.comma=','}},
            {.tokenType = TokenType::number,
                    .token = {.number=6}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::division}}},
            {.tokenType = TokenType::number,
                    .token = {.number=5}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::addition}}},
            {.tokenType = TokenType::number,
                    .token = {.number=2}},
            {.tokenType = TokenType::comma,
                    .token = {.comma=','}},
            {.tokenType = TokenType::number,
                    .token = {.number=2}},
            {.tokenType = TokenType::bracket,
                    .token = {.bracket={.type=calculator::Bracket::Type::right}}},
            {.tokenType = TokenType::comma,
                    .token = {.comma=','}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::negation}}},
            {.tokenType = TokenType::number,
                    .token = {.number=80}},
            {.tokenType = TokenType::comma,
                    .token = {.comma=','}},
            {.tokenType = TokenType::function,
                    .token = {.function={.type=Function::Type::condition,
                                         .argc=3}}},
            {.tokenType = TokenType::bracket,
                    .token = {.bracket={.type=calculator::Bracket::Type::left}}},
            {.tokenType = TokenType::number,
                    .token = {.number=66}},
            {.tokenType = TokenType::comma,
                    .token = {.comma=','}},
            {.tokenType = TokenType::number,
                    .token = {.number=35}},
            {.tokenType = TokenType::comma,
                    .token = {.comma=','}},
            {.tokenType = TokenType::number,
                    .token = {.number=77}},
            {.tokenType = TokenType::bracket,
                    .token = {.bracket={.type=calculator::Bracket::Type::right}}},
            {.tokenType = TokenType::comma,
                    .token = {.comma=','}},
            {.tokenType = TokenType::number,
                    .token = {.number=50}},
            {.tokenType = TokenType::comma,
                    .token = {.comma=','}},
            {.tokenType = TokenType::number,
                    .token = {.number=60}},
            {.tokenType = TokenType::bracket,
                    .token = {.bracket={.type=calculator::Bracket::Type::right}}},
            {.tokenType = TokenType::operation,
                    .token = {.operation={.type=Operation::Type::multiplying}}},
            {.tokenType = TokenType::number,
                    .token = {.number=3}},
    };

    std::stringstream stream(inputExpression);
    InputReader inputReader(stream);
    std::list<Symbol> actualSymbols;

    Symbol *lastSymbol;
    lastSymbol = inputReader.getNextSymbol();
    while (lastSymbol->tokenType != TokenType::end) {
        actualSymbols.emplace_back(*lastSymbol);
        delete lastSymbol;
        lastSymbol = inputReader.getNextSymbol();
    }
    delete lastSymbol;

    EXPECT_EQ(expectedSymbols, actualSymbols);
}