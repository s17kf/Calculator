//
// Created by stefan on 13/03/24.
//

#ifndef CALCULATORAADS_SYMBOL_H
#define CALCULATORAADS_SYMBOL_H

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

        [[nodiscard]] const char *str() const {
            switch (type) {
                case Type::addition:
                    return "+";
                case Type::subtraction:
                    return "-";
                case Type::multiplying:
                    return "*";
                case Type::division:
                    return "/";
            }
        }

        bool operator==(const Operation &other) const {
            return type == other.type;
        }
    };

    struct Function {
        enum class Type {
            condition, negation, min, max,
        };

        Type type;

        [[nodiscard]] const char *str() const {
            switch (type) {
                case Type::condition:
                    return "IF";
                case Type::negation:
                    return "N";
                case Type::min:
                    return "MIN";
                case Type::max:
                    return "MAX";
            }
        }

        bool operator==(const Function &other) const {
            return type == other.type;
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

    bool operator==(const Symbol &s1, const Symbol s2);

} // calculator

#endif //CALCULATORAADS_SYMBOL_H
