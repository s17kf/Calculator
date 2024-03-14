//
// Created by stefan on 13/03/24.
//

#include <sstream>
#include "gtest/gtest.h"

#include "Symbol.h"

using calculator::Symbol;
using calculator::TokenType;

using calculator::Operation;
using calculator::Function;
using calculator::Bracket;

class SymbolTest : public ::testing::Test {
protected:
    void verifyStreamResult(const Symbol &symbol, const std::string &expectedContent) {
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
            .token={.function={.type=Function::Type::condition}}};
    Symbol negation{.tokenType=calculator::TokenType::function,
            .token={.function={.type=Function::Type::negation}}};
    Symbol min{.tokenType=calculator::TokenType::function,
            .token={.function={.type=Function::Type::min}}};
    Symbol max{.tokenType=calculator::TokenType::function,
            .token={.function={.type=Function::Type::max}}};
    verifyStreamResult(condition, "IF");
    verifyStreamResult(negation, "N");
    verifyStreamResult(min, "MIN");
    verifyStreamResult(max, "MAX");


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