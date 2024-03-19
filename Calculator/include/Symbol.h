//
// Created by stefan on 13/03/24.
//

#ifndef CALCULATORAADS_SYMBOL_H
#define CALCULATORAADS_SYMBOL_H

#include "List.h"
#include <memory>

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

        Operation(Operation::Type type) : type(type) {}

        [[nodiscard]] const char *str() const;

        int operator()(int a, int b) const;

        bool operator==(const Operation &other) const {
            return type == other.type;
        }

        unsigned int prio() const;

        Type type;
    };

    struct Function {
        enum class Type {
            condition, negation, min, max,
        };

        Function(Function::Type type, unsigned int argc = 1) : type(type), argc(argc) {}

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

        Bracket(Bracket::Type type) : type(type) {}

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
        Token(int number) : number(number) {}

        Token(Operation *operation) : operation(operation) {}

        Token(Function *function) : function(function) {}

        Token(Bracket *bracket) : bracket(bracket) {}

        Token(char c) {
            if (c == ',') {
                comma = c;
                return;
            }
            end = c;
        }

        ~Token() {}


        int number;
        std::unique_ptr<Operation> operation;
        std::unique_ptr<Function> function;
        std::unique_ptr<Bracket> bracket;
        char comma;
        char end;
    };

    struct Symbol {
        Symbol(TokenType tokenType, Token *other) : tokenType(tokenType), token(other) {}

        ~Symbol() {
            switch (tokenType) {
                case TokenType::operation:
                    token->operation.reset();
                    break;
                case TokenType::function:
                    token->function.reset();
                case TokenType::bracket:
                    token->bracket.reset();
            }
            delete token;
        }

        TokenType tokenType;
        Token *token;
    };

    std::ostream &operator<<(std::ostream &stream, const Bracket &bracket);

    std::ostream &operator<<(std::ostream &stream, const Symbol &symbol);

    bool operator==(const Symbol &s1, const Symbol &s2);

    bool operator<(const Operation &o1, const Operation &o2);

    bool operator<=(const Operation &o1, const Operation &o2);

} // calculator

#endif //CALCULATORAADS_SYMBOL_H
