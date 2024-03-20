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
            Symbol(TokenType::number, 2),
            Symbol(TokenType::number, 100),
            Symbol(TokenType::number, 1),
            Symbol(TokenType::number, 6),
            Symbol(TokenType::number, 5),
            Symbol(TokenType::operation, Operation(Operation::Type::division)),
            Symbol(TokenType::number, 2),
            Symbol(TokenType::operation, Operation(Operation::Type::addition)),
            Symbol(TokenType::number, 2),
            Symbol(TokenType::function, Function(calculator::Function::Type::max, 3)),
            Symbol(TokenType::number, 80),
            Symbol(TokenType::function, Function(calculator::Function::Type::negation, 1)),
            Symbol(TokenType::number, 66),
            Symbol(TokenType::number, 35),
            Symbol(TokenType::number, 77),
            Symbol(TokenType::function, Function(calculator::Function::Type::condition, 3)),
            Symbol(TokenType::number, 50),
            Symbol(TokenType::number, 60),
            Symbol(TokenType::function, Function(calculator::Function::Type::min, 6)),
            Symbol(TokenType::number, 3),
            Symbol(TokenType::operation, Operation(Operation::Type::multiplying)),
            Symbol(TokenType::operation, Operation(Operation::Type::addition)),
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
            Symbol(TokenType::number, 400),
            Symbol(TokenType::function, Function(calculator::Function::Type::negation, 1)),
            Symbol(TokenType::number, 11),
            Symbol(TokenType::number, 3),
            Symbol(TokenType::number, 2),
            Symbol(TokenType::operation, Operation(Operation::Type::multiplying)),
            Symbol(TokenType::operation, Operation(Operation::Type::subtraction)),
            Symbol(TokenType::number, 2),
            Symbol(TokenType::operation, Operation(Operation::Type::division)),
            Symbol(TokenType::operation, Operation(Operation::Type::addition)),
            Symbol(TokenType::number, 200),
            Symbol(TokenType::function, Function(calculator::Function::Type::negation, 1)),
            Symbol(TokenType::function, Function(calculator::Function::Type::negation, 1)),
            Symbol(TokenType::operation, Operation(Operation::Type::addition)),
    };

    std::stringstream inputStream(inputExpression);
    InputReader inputReader(inputStream);
    InputConverter inputConverter(inputReader);

    inputConverter.convertFormula();

    verifyFormula(inputConverter, expectedSymbols);
}