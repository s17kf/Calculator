//
// Created by stefan on 14/03/24.
//

#include "gtest/gtest.h"
#include <list>
#include <sstream>
#include <ranges>

#include "InputReader.h"
#include "Symbol.h"
#include "UserInputReaderStub.h"

using calculator::InputReader;
using calculator::Symbol;
using calculator::TokenType;

using calculator::Operation;
using calculator::Function;
using calculator::Bracket;
using calculator::Token;

using input_output::UserInputReaderStub;

class InputReaderTest : public ::testing::Test {
protected:
};

TEST_F(InputReaderTest, validMultiTypeInputTest) {
    const std::string inputExpression =
            "2 + MIN ( 100 , MAX ( 1 , 6 / 5 + 2 , 2 ) , N 80 ,  IF ( 66  , 35 , 77 ) , 50 , 60 ) * 3 .";

    const std::list<Symbol> expectedSymbols{
            Symbol(TokenType::number, 2),
            Symbol(TokenType::operation, Operation(Operation::Type::addition)),
            Symbol(TokenType::function, Function(Function::Type::min, 1)),
            Symbol(TokenType::bracket, Bracket(Bracket::Type::left)),
            Symbol(TokenType::number, 100),
            Symbol(TokenType::comma, ','),
            Symbol(TokenType::function, Function(Function::Type::max, 1)),
            Symbol(TokenType::bracket, Bracket(Bracket::Type::left)),
            Symbol(TokenType::number, 1),
            Symbol(TokenType::comma, ','),
            Symbol(TokenType::number, 6),
            Symbol(TokenType::operation, Operation(Operation::Type::division)),
            Symbol(TokenType::number, 5),
            Symbol(TokenType::operation, Operation(Operation::Type::addition)),
            Symbol(TokenType::number, 2),
            Symbol(TokenType::comma, ','),
            Symbol(TokenType::number, 2),
            Symbol(TokenType::bracket, Bracket(Bracket::Type::right)),
            Symbol(TokenType::comma, ','),
            Symbol(TokenType::function, Function(Function::Type::negation, 1)),
            Symbol(TokenType::number, 80),
            Symbol(TokenType::comma, ','),
            Symbol(TokenType::function, Function(Function::Type::condition, 1)),
            Symbol(TokenType::bracket, Bracket(Bracket::Type::left)),
            Symbol(TokenType::number, 66),
            Symbol(TokenType::comma, ','),
            Symbol(TokenType::number, 35),
            Symbol(TokenType::comma, ','),
            Symbol(TokenType::number, 77),
            Symbol(TokenType::bracket, Bracket(Bracket::Type::right)),
            Symbol(TokenType::comma, ','),
            Symbol(TokenType::number, 50),
            Symbol(TokenType::comma, ','),
            Symbol(TokenType::number, 60),
            Symbol(TokenType::bracket, Bracket(Bracket::Type::right)),
            Symbol(TokenType::operation, Operation(Operation::Type::multiplying)),
            Symbol(TokenType::number, 3),
    };

    UserInputReaderStub userInputReaderStub(inputExpression);
    InputReader inputReader(userInputReaderStub);
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