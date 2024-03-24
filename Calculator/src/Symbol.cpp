//
// Created by stefan on 14/03/24.
//

#include "Symbol.h"
#include "String.h"

namespace calculator {

    using data_structures::String;

    String Operation::str() const {
        switch (type) {
            case Type::addition:
                return String('+');
            case Type::subtraction:
                return String('-');
            case Type::multiplying:
                return String('*');
            case Type::division:
                return String('/');
        }
        throw std::invalid_argument("Invalid type in operation->str() conversion");
    }

    int Operation::operator()(int a, int b) const {
        switch (type) {
            case Type::addition:
                return a + b;
            case Type::subtraction:
                return b - a;
            case Type::multiplying:
                return a * b;
            case Type::division:
                if (a == 0)
                    throw std::overflow_error("Divide by zero!");
                return b / a;
        }
        throw std::invalid_argument("Invalid type in operation->()");
    }

    String Function::str() const {
        switch (type) {
            case Type::condition:
                return String("IF");
            case Type::negation:
                return String("N");
            case Type::min:
                return String("MIN") + argc;
            case Type::max:
                return String("MAX") + argc;
        }
        throw std::invalid_argument("Invalid type in function->str() conversion");
    }

    String Bracket::str() const {
        switch (type) {
            case Type::left:
                return String('(');
            case Type::right:
                return String(')');
        }
        throw std::invalid_argument("Invalid type in bracket->str() conversion");
    }

    data_structures::String Symbol::str() const {
        switch (tokenType) {
            case TokenType::number:
                return String() + token.number;
            case TokenType::operation:
                return token.operation.str();
            case TokenType::function:
                return token.function.str();
            case TokenType::bracket:
                return token.bracket.str();
            case TokenType::comma:
                return String(token.comma);
            case TokenType::end:
                return String(token.end);
        }
        throw std::invalid_argument("Invalid type in symbol->str() conversion");
    }

    bool operator==(const Symbol &s1, const Symbol &s2) {
        if (s1.tokenType != s2.tokenType)
            return false;
        switch (s1.tokenType) {
            case TokenType::number:
                return s1.token.number == s2.token.number;
            case TokenType::operation:
                return s1.token.operation == s2.token.operation;
            case TokenType::function:
                return s1.token.function == s2.token.function;
            case TokenType::bracket:
                return s1.token.bracket == s2.token.bracket;
            case TokenType::comma:
            case TokenType::end:
                return true;
        }
        throw std::invalid_argument("Invalid type in symbol->== operator");
    }

    unsigned int Operation::prio() const {
        switch (type) {
            case Type::addition:
            case Type::subtraction:
                return 0;
            case Type::multiplying:
            case Type::division:
                return 1;
        }
        throw std::invalid_argument("Invalid type in operation->prio()");
    }
}
