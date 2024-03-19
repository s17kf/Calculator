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
using calculator::Token;

using calculator::Operation;
using calculator::Function;
using calculator::Bracket;


class InputConverterTest : public ::testing::Test {
protected:
    static void verifyFormula(InputConverter &inputConverter, const std::vector<Symbol *> &expectedSymbols) {
        uint readSymbols = 0;
        while (inputConverter.symbolsLeft()) {
            Symbol *symbol = inputConverter.removeNextSymbol();
            ASSERT_EQ(*expectedSymbols[readSymbols], *symbol) << "Wrong symbol at index: " << readSymbols;
            delete symbol;
            ++readSymbols;
        }
        ASSERT_EQ(expectedSymbols.size(), readSymbols);
    }
};

TEST_F(InputConverterTest, convertingFormula) {
    const std::string inputExpression =
            "2 + MIN ( 100 , MAX ( 1 , 6 / 5 + 2 , 2 ) , N 80 ,  IF ( 66  , 35 , 77 ) , 50 , 60 ) * 3 .";
    const std::vector<Symbol *> expectedSymbols{
            new Symbol(TokenType::number, new Token(2)),
            new Symbol(TokenType::number, new Token(100)),
            new Symbol(TokenType::number, new Token(1)),
            new Symbol(TokenType::number, new Token(6)),
            new Symbol(TokenType::number, new Token(5)),
            new Symbol(TokenType::operation,
                       new Token(new Operation(Operation::Type::division))),
            new Symbol(TokenType::number, new Token(2)),
            new Symbol(TokenType::operation,
                       new Token(new Operation(Operation::Type::addition))),
            new Symbol(TokenType::number, new Token(2)),
            new Symbol(TokenType::function,
                       new Token(new Function(calculator::Function::Type::max, 3))),
            new Symbol(TokenType::number, new Token(80)),
            new Symbol(TokenType::function,
                       new Token(new Function(calculator::Function::Type::negation, 1))),
            new Symbol(TokenType::number, new Token(66)),
            new Symbol(TokenType::number, new Token(35)),
            new Symbol(TokenType::number, new Token(77)),
            new Symbol(TokenType::function,
                       new Token(new Function(calculator::Function::Type::condition, 3))),
            new Symbol(TokenType::number, new Token(50)),
            new Symbol(TokenType::number, new Token(60)),
            new Symbol(TokenType::function,
                       new Token(new Function(calculator::Function::Type::min, 6))),
            new Symbol(TokenType::number, new Token(3)),
            new Symbol(TokenType::operation,
                       new Token(new Operation(Operation::Type::multiplying))),
            new Symbol(TokenType::operation,
                       new Token(new Operation(Operation::Type::addition))),
    };

    std::stringstream inputStream(inputExpression);
    InputReader inputReader(inputStream);
    InputConverter inputConverter(inputReader);

    inputConverter.convertFormula();

    verifyFormula(inputConverter, expectedSymbols);

    for (auto *symbol: expectedSymbols) {
        delete symbol;
    }
}

TEST_F(InputConverterTest, convertingFormula2) {
    const std::string inputExpression =
            "N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .";
    const std::vector<Symbol *> expectedSymbols{
            new Symbol(TokenType::number,new Token(400)),
            new Symbol(TokenType::function,
                        new Token(new Function(calculator::Function::Type::negation, 1))),
            new Symbol(TokenType::number,new Token(11)),
            new Symbol(TokenType::number,new Token(3)),
            new Symbol(TokenType::number,new Token(2)),
            new Symbol(TokenType::operation,
                        new Token(new Operation(Operation::Type::multiplying))),
            new Symbol(TokenType::operation,
                        new Token(new Operation(Operation::Type::subtraction))),
            new Symbol(TokenType::number,new Token(2)),
            new Symbol(TokenType::operation,
                       new Token(new Operation(Operation::Type::division))),
            new Symbol(TokenType::operation,
                       new Token(new Operation(Operation::Type::addition))),
            new Symbol(TokenType::number,new Token(200)),
            new Symbol(TokenType::function,
                       new Token(new Function(calculator::Function::Type::negation, 1))),
            new Symbol(TokenType::function,
                       new Token(new Function(calculator::Function::Type::negation, 1))),
            new Symbol(TokenType::operation,
                       new Token(new Operation(Operation::Type::addition))),
    };

    std::stringstream inputStream(inputExpression);
    InputReader inputReader(inputStream);
    InputConverter inputConverter(inputReader);

    inputConverter.convertFormula();

    verifyFormula(inputConverter, expectedSymbols);

    for (auto *symbol: expectedSymbols) {
        delete symbol;
    }
}