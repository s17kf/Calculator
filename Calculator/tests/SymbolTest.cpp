//
// Created by stefan on 13/03/24.
//

#include <sstream>
#include "gtest/gtest.h"

#include "Symbol.h"
#include "List.h"

using calculator::Symbol;
using calculator::TokenType;

using calculator::Operation;
using calculator::Function;
using calculator::Bracket;
using calculator::Token;

using data_structures::List;

class SymbolTest : public ::testing::Test {
protected:
    static void verifyStrResult(const Symbol &symbol, const std::string &expectedContent) {
        ASSERT_EQ(expectedContent, symbol.str().c_str());
    }

};

TEST_F(SymbolTest, SymbolStrTest) {
    Symbol number(TokenType::number, 1234);
    verifyStrResult(number, "1234");

    Symbol plus(calculator::TokenType::operation, Operation(Operation::Type::addition));
    Symbol minus(calculator::TokenType::operation, Operation(Operation::Type::subtraction));
    Symbol multiply(calculator::TokenType::operation, Operation(Operation::Type::multiplying));
    Symbol divide(calculator::TokenType::operation, Operation(Operation::Type::division));
    verifyStrResult(plus, "+");
    verifyStrResult(minus, "-");
    verifyStrResult(multiply, "*");
    verifyStrResult(divide, "/");

    Symbol condition(calculator::TokenType::function, Function(Function::Type::condition));
    Symbol negation(calculator::TokenType::function, Function(Function::Type::negation));
    Symbol min(calculator::TokenType::function, Function(Function::Type::min, 0));
    Symbol max(calculator::TokenType::function, Function(Function::Type::max, 0));
    verifyStrResult(condition, "IF");
    verifyStrResult(negation, "N");
    verifyStrResult(min, "MIN0");
    verifyStrResult(max, "MAX0");

    Symbol bracketLeft(TokenType::bracket, Bracket(Bracket::Type::left));
    Symbol bracketRight(TokenType::bracket, Bracket(Bracket::Type::right));
    verifyStrResult(bracketLeft, "(");
    verifyStrResult(bracketRight, ")");

    Symbol comma(TokenType::comma, ',');
    Symbol dot(TokenType::end, '.');
    verifyStrResult(comma, ",");
    verifyStrResult(dot, ".");
}

TEST_F(SymbolTest, operationsGiveProperResults) {
    const auto plus = Operation(Operation::Type::addition);
    const auto minus = Operation(Operation::Type::subtraction);
    const auto multiply = Operation(Operation::Type::multiplying);
    const auto divide = Operation(Operation::Type::division);

    ASSERT_EQ(11, plus(5, 6));
    ASSERT_EQ(-1, minus(3, 2));
    ASSERT_EQ(20, multiply(4, 5));
    ASSERT_EQ(2, divide(3, 7));
    ASSERT_THROW(divide(0, 4), std::overflow_error);
}
