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
        uint argc;

        [[nodiscard]] const char *str() const {
            switch (type) {
                case Type::condition: {
                    char *result = new char[4];
                    sprintf(result, "IF");
                    sprintf(&result[2], "%d", argc);
                    return result;
                }
                case Type::negation: {
                    char *result = new char[2];
                    sprintf(result, "N");
                    return result;
                }
                case Type::min: {
                    char *result = new char[10];
                    sprintf(result, "MIN");
                    sprintf(&result[3], "%d", argc);
                    return result;
                }
                case Type::max: {
                    char *result = new char[10];
                    sprintf(result, "MAX");
                    sprintf(&result[3], "%d", argc);
                    return result;
                }
            }
        }

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
