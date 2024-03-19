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

        Type type;

        [[nodiscard]] const char *str() const;

        int operator()(int a, int b) const;

        bool operator==(const Operation &other) const {
            return type == other.type;
        }

        unsigned int prio() const;
    };

    struct Function {
        enum class Type {
            condition, negation, min, max,
        };

        Type type;
        unsigned int argc;

        [[nodiscard]] const char *str() const;

        int operator()(data_structures::List<int> &args) const;

        bool operator==(const Function &other) const {
            return type == other.type && argc == other.argc;
        }
    };

    struct Bracket {
        enum class Type {
            left, right,
        };

        Type type;

        [[nodiscard]] const char *str() const {
            switch (type) {
                case Type::left:
                    return "(";
                case Type::right:
                    return ")";
            }
        }

        bool operator==(const Bracket &other) const {
            return type == other.type;
        }
    };


    union Token {
        int number;
        Operation operation;
        Function function;
        Bracket bracket;
        char comma;
        char end;
    };

    struct Symbol {
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
