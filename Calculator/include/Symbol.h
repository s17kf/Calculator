//
// Created by stefan on 13/03/24.
//

#ifndef CALCULATORAADS_SYMBOL_H
#define CALCULATORAADS_SYMBOL_H

#include "List.h"

namespace calculator {

    enum class TokenType {
        number,
        operation,
        function,
        bracket,
        comma,
        end,
    };

    struct Operation {
        enum class Type {
            addition, subtraction, multiplying, division,
        };

        explicit Operation(Operation::Type type) : type(type) {}

        [[nodiscard]] const char *str() const;

        int operator()(int a, int b) const;

        bool operator==(const Operation &other) const {
            return type == other.type;
        }

        [[nodiscard]] unsigned int prio() const;

        Type type;
    };

    struct Function {
        enum class Type {
            condition, negation, min, max,
        };

        explicit Function(Function::Type type, unsigned int argc = 1) : type(type), argc(argc) {}

        [[nodiscard]] const char *str() const;

        int operator()(data_structures::List<int> &args) const;

        bool operator==(const Function &other) const {
            return type == other.type && argc == other.argc;
        }

        Type type;
        unsigned int argc;
    };

    struct Bracket {
        enum class Type {
            left, right,
        };

        explicit Bracket(Bracket::Type type) : type(type) {}

        [[nodiscard]] const char *str() const {
            switch (type) {
                case Type::left:
                    return "(";
                case Type::right:
                    return ")";
            }
            throw std::invalid_argument("Invalid type in bracket->str() conversion");
        }

        bool operator==(const Bracket &other) const {
            return type == other.type;
        }

        Type type;
    };


    union Token {
        explicit Token(int number) : number(number) {}

        explicit Token(Operation operation) : operation(operation) {}

        explicit Token(Function function) : function(function) {}

        explicit Token(Bracket bracket) : bracket(bracket) {}

        explicit Token(char c) {
            if (c == ',') {
                comma = c;
                return;
            }
            end = c;
        }

        ~Token() {}

        int number;
        Operation operation;
        Function function;
        Bracket bracket;
        char comma;
        char end;
    };

    struct Symbol {
        Symbol(TokenType tokenType, int number) : tokenType(tokenType), token(number) {}

        Symbol(TokenType tokenType, Operation operation) : tokenType(tokenType), token(operation) {}

        Symbol(TokenType tokenType, Function function) : tokenType(tokenType), token(function) {}

        Symbol(TokenType tokenType, Bracket bracket) : tokenType(tokenType), token(bracket) {}

        Symbol(TokenType tokenType, char c) : tokenType(tokenType), token(c) {}

        TokenType tokenType;
        Token token;
    };

    std::ostream &operator<<(std::ostream &stream, const Bracket &bracket);

    std::ostream &operator<<(std::ostream &stream, const Symbol &symbol);

    bool operator==(const Symbol &s1, const Symbol &s2);

    bool operator<(const Operation &o1, const Operation &o2);

    bool operator<=(const Operation &o1, const Operation &o2);

} // calculator

#endif //CALCULATORAADS_SYMBOL_H
