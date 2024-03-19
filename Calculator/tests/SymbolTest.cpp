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
    Symbol number{.tokenType = TokenType::number, .token = {.number=1234}};
    verifyStreamResult(number, "1234");

    Symbol plus{.tokenType=calculator::TokenType::operation,
            .token={.operation={.type=Operation::Type::addition}}};
    Symbol minus{.tokenType=calculator::TokenType::operation,
            .token={.operation={.type=Operation::Type::subtraction}}};
    Symbol multiply{.tokenType=calculator::TokenType::operation,
            .token={.operation={.type=Operation::Type::multiplying}}};
    Symbol divide{.tokenType=calculator::TokenType::operation,
            .token={.operation={.type=Operation::Type::division}}};
    verifyStreamResult(plus, "+");
    verifyStreamResult(minus, "-");
    verifyStreamResult(multiply, "*");
    verifyStreamResult(divide, "/");


    Symbol condition{.tokenType=calculator::TokenType::function,
            .token={.function={.type=Function::Type::condition,
                    .argc=0}}};
    Symbol negation{.tokenType=calculator::TokenType::function,
            .token={.function={.type=Function::Type::negation}}};
    Symbol min{.tokenType=calculator::TokenType::function,
            .token={.function={.type=Function::Type::min,
                    .argc=0}}};
    Symbol max{.tokenType=calculator::TokenType::function,
            .token={.function={.type=Function::Type::max,
                    .argc=0}}};
    verifyStreamResult(condition, "IF");
    verifyStreamResult(negation, "N");
    verifyStreamResult(min, "MIN0");
    verifyStreamResult(max, "MAX0");


    Symbol bracketLeft{.tokenType = TokenType::bracket,
            .token = {.bracket={.type=Bracket::Type::left}}};
    Symbol bracketRight{.tokenType = TokenType::bracket,
            .token = {.bracket={.type=Bracket::Type::right}}};
    verifyStreamResult(bracketLeft, "(");
    verifyStreamResult(bracketRight, ")");


    Symbol comma{.tokenType = TokenType::comma, .token = {.comma=','}};
    Symbol dot{.tokenType = TokenType::end, .token = {.end='.'}};
    verifyStreamResult(comma, ",");
    verifyStreamResult(dot, ".");
}

TEST_F(SymbolTest, operationsGiveProperResults) {
    const auto plus = Operation{.type=Operation::Type::addition};
    const auto minus = Operation{.type=Operation::Type::subtraction};
    const auto multiply = Operation{.type=Operation::Type::multiplying};
    const auto divide = Operation{.type=Operation::Type::division};

    ASSERT_EQ(11, plus(5, 6));
    ASSERT_EQ(-1, minus(3, 2));
    ASSERT_EQ(20, multiply(4, 5));
    ASSERT_EQ(2, divide(3, 7));
    ASSERT_THROW(divide(0, 4), std::overflow_error);
}

TEST_F(SymbolTest, conditionGiveProperResults) {
    const auto cond = Function{.type=Function::Type::condition,
            .argc=3};

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
    const auto negation = Function{.type=Function::Type::negation,
            .argc=1};

    List<int> list1;
    list1.pushBack(6);
    ASSERT_EQ(-6, negation(list1));

    List<int> list2;
    list2.pushBack(-4);
    ASSERT_EQ(4, negation(list2));
}

TEST_F(SymbolTest, maxGiveProperResults) {
    const auto max = Function{.type=Function::Type::max,
            .argc=4};

    List<int> list1;
    list1.pushBack(4);
    list1.pushBack(3);
    list1.pushBack(8);
    list1.pushBack(6);
    ASSERT_EQ(8, max(list1));
}

TEST_F(SymbolTest, minGiveProperResults) {
    const auto min = Function{.type=Function::Type::min,
            .argc=5};

    List<int> list1;
    list1.pushBack(4);
    list1.pushBack(3);
    list1.pushBack(8);
    list1.pushBack(2);
    list1.pushBack(6);
    ASSERT_EQ(2, min(list1));
}