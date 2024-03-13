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
    };

    std::ostream &operator<<(std::ostream &stream, const Bracket bracket) {
        stream << bracket.str();
        return stream;
    }

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

    std::ostream &operator<<(std::ostream &stream, const Symbol symbol) {
        switch (symbol.tokenType) {
            case TokenType::number:
                stream << symbol.token.number;
                break;
            case TokenType::operation:
                stream << symbol.token.operation.str();
                break;
            case TokenType::function:
                stream << symbol.token.function.str();
                break;
            case TokenType::bracket:
                stream << symbol.token.bracket;
                break;
            case TokenType::comma:
                stream << symbol.token.comma;
                break;
            case TokenType::end:
                stream << symbol.token.end;
                break;
        }
        return stream;
    }

} // calculator

#endif //CALCULATORAADS_SYMBOL_H
