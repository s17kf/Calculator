//
// Created by stefan on 14/03/24.
//

#include <ostream>

#include "Symbol.h"

namespace calculator {
    std::ostream &operator<<(std::ostream &stream, const Bracket &bracket) {
        stream << bracket.str();
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, const Symbol &symbol) {
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
                stream << ',';
                break;
            case TokenType::end:
                stream << symbol.token.end;
                break;
            default:
                throw std::invalid_argument("Invalid symbol in stream opertator!");
        }
        return stream;
    }

    bool operator==(const Symbol &s1, const Symbol s2) {
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
    }
}