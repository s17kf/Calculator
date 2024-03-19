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
    static void verifyStreamResult(const Symbol &symbol, const std::string &expectedContent) {
        std::stringstream stream;
        stream << symbol;
        ASSERT_EQ(expectedContent, stream.str());
    }

};

TEST_F(SymbolTest, SymbolStrTest) {
    auto *numberToken = new Token(1234);
    Symbol number(TokenType::number, numberToken);
    verifyStreamResult(number, "1234");

    auto *plusOperation = new Operation(Operation::Type::addition);
    auto *plusToken = new Token(plusOperation);
    auto *minusOperation = new Operation(Operation::Type::subtraction);
    auto *minusToken = new Token(minusOperation);
    auto *multiplyOperation = new Operation(Operation::Type::multiplying);
    auto *multiplyToken = new Token(multiplyOperation);
    auto *divideOperation = new Operation(Operation::Type::division);
    auto *divideToken = new Token(divideOperation);
    Symbol plus(calculator::TokenType::operation, plusToken);
    Symbol minus(calculator::TokenType::operation, minusToken);
    Symbol multiply(calculator::TokenType::operation, multiplyToken);
    Symbol divide(calculator::TokenType::operation, divideToken);
    verifyStreamResult(plus, "+");
    verifyStreamResult(minus, "-");
    verifyStreamResult(multiply, "*");
    verifyStreamResult(divide, "/");

    auto *condFunction = new Function(Function::Type::condition, 0);
    auto *condToken = new Token(condFunction);
    auto *negationFunction = new Function(Function::Type::negation, 0);
    auto *negationToken = new Token(negationFunction);
    auto *minFunction = new Function(Function::Type::min, 0);
    auto *minToken = new Token(minFunction);
    auto *maxFunction = new Function(Function::Type::max, 0);
    auto *maxToken = new Token(maxFunction);
    Symbol condition(calculator::TokenType::function, condToken);
    Symbol negation(calculator::TokenType::function, negationToken);
    Symbol min(calculator::TokenType::function, minToken);
    Symbol max(calculator::TokenType::function, maxToken);
    verifyStreamResult(condition, "IF");
    verifyStreamResult(negation, "N");
    verifyStreamResult(min, "MIN0");
    verifyStreamResult(max, "MAX0");

    auto *leftBracket = new Bracket(Bracket::Type::left);
    auto *leftToken = new Token(leftBracket);
    auto *rightBracket = new Bracket(Bracket::Type::right);
    auto rightToken = new Token(rightBracket);
    Symbol bracketLeft(TokenType::bracket, leftToken);
    Symbol bracketRight(TokenType::bracket, rightToken);
    verifyStreamResult(bracketLeft, "(");
    verifyStreamResult(bracketRight, ")");


    auto *commaToken = new Token(',');
    auto *dotToken = new Token('.');
    Symbol comma(TokenType::comma, commaToken);
    Symbol dot(TokenType::end, dotToken);
    verifyStreamResult(comma, ",");
    verifyStreamResult(dot, ".");
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

TEST_F(SymbolTest, conditionGiveProperResults) {
    const auto cond = Function(Function::Type::condition, 3);

    List<int> list1;
    list1.pushBack(6);
    list1.pushBack(5);
    list1.pushBack(3);
    ASSERT_EQ(5, cond(list1));

    List<int> list2;
    list2.pushBack(3);
    list2.pushBack(5);
    list2.pushBack(-4);
    ASSERT_EQ(3, cond(list2));
}

TEST_F(SymbolTest, negationGiveProperResults) {
    const auto negation = Function(Function::Type::negation, 1);

    List<int> list1;
    list1.pushBack(6);
    ASSERT_EQ(-6, negation(list1));

    List<int> list2;
    list2.pushBack(-4);
    ASSERT_EQ(4, negation(list2));
}

TEST_F(SymbolTest, maxGiveProperResults) {
    const auto max = Function(Function::Type::max, 4);

    List<int> list1;
    list1.pushBack(4);
    list1.pushBack(3);
    list1.pushBack(8);
    list1.pushBack(6);
    ASSERT_EQ(8, max(list1));
}

TEST_F(SymbolTest, minGiveProperResults) {
    const auto min = Function(Function::Type::min, 5);

    List<int> list1;
    list1.pushBack(4);
    list1.pushBack(3);
    list1.pushBack(8);
    list1.pushBack(2);
    list1.pushBack(6);
    ASSERT_EQ(2, min(list1));
}
