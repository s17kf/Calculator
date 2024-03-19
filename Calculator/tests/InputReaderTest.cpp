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
using calculator::Token;

class InputReaderTest : public ::testing::Test {
protected:
};

TEST_F(InputReaderTest, validMultiTypeInputTest) {
    const std::string inputExpression =
            "2 + MIN ( 100 , MAX ( 1 , 6 / 5 + 2 , 2 ) , N 80 ,  IF ( 66  , 35 , 77 ) , 50 , 60 ) * 3 .";

    const std::list<Symbol *> expectedSymbols{
            new Symbol(TokenType::number, new Token(2)),
            new Symbol(TokenType::operation, new Token(new Operation(Operation::Type::addition))),
            new Symbol(TokenType::function, new Token(new Function(Function::Type::min, 1))),
            new Symbol(TokenType::bracket, new Token(new Bracket(Bracket::Type::left))),
            new Symbol(TokenType::number, new Token(100)),
            new Symbol(TokenType::comma, new Token(',')),
            new Symbol(TokenType::function, new Token(new Function(Function::Type::max, 1))),
            new Symbol(TokenType::bracket, new Token(new Bracket(Bracket::Type::left))),
            new Symbol(TokenType::number, new Token(1)),
            new Symbol(TokenType::comma, new Token(',')),
            new Symbol(TokenType::number, new Token(6)),
            new Symbol(TokenType::operation, new Token(new Operation(Operation::Type::division))),
            new Symbol(TokenType::number, new Token(5)),
            new Symbol(TokenType::operation, new Token(new Operation(Operation::Type::addition))),
            new Symbol(TokenType::number, new Token(2)),
            new Symbol(TokenType::comma, new Token(',')),
            new Symbol(TokenType::number, new Token(2)),
            new Symbol(TokenType::bracket, new Token(new Bracket(Bracket::Type::right))),
            new Symbol(TokenType::comma, new Token(',')),
            new Symbol(TokenType::function, new Token(new Function(Function::Type::negation, 1))),
            new Symbol(TokenType::number, new Token(80)),
            new Symbol(TokenType::comma, new Token(',')),
            new Symbol(TokenType::function, new Token(new Function(Function::Type::condition, 1))),
            new Symbol(TokenType::bracket, new Token(new Bracket(Bracket::Type::left))),
            new Symbol(TokenType::number, new Token(66)),
            new Symbol(TokenType::comma, new Token(',')),
            new Symbol(TokenType::number, new Token(35)),
            new Symbol(TokenType::comma, new Token(',')),
            new Symbol(TokenType::number, new Token(77)),
            new Symbol(TokenType::bracket, new Token(new Bracket(Bracket::Type::right))),
            new Symbol(TokenType::comma, new Token(',')),
            new Symbol(TokenType::number, new Token(50)),
            new Symbol(TokenType::comma, new Token(',')),
            new Symbol(TokenType::number, new Token(60)),
            new Symbol(TokenType::bracket, new Token(new Bracket(Bracket::Type::right))),
            new Symbol(TokenType::operation, new Token(new Operation(Operation::Type::multiplying))),
            new Symbol(TokenType::number, new Token(3)),
    };

    std::stringstream stream(inputExpression);
    InputReader inputReader(stream);
    std::list<Symbol *> actualSymbols;

    Symbol *lastSymbol;
    lastSymbol = inputReader.getNextSymbol();
    auto expectedSymbolIt = expectedSymbols.begin();
    while (lastSymbol->tokenType != TokenType::end) {
        ASSERT_EQ(*(*expectedSymbolIt++), *lastSymbol);
        delete lastSymbol;
        lastSymbol = inputReader.getNextSymbol();
    }
    delete lastSymbol;

    for (auto *symbol : expectedSymbols) {
        delete symbol;
    }
}