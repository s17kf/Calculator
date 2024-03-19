//
// Created by stefan on 14/03/24.
//

#include <ostream>

#include "Symbol.h"

namespace calculator {

    const char *Operation::str() const {
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
    }

    const char *Function::str() const {
        switch (type) {
            case Type::condition: {
                char *result = new char[3];
                sprintf(result, "IF");
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

    int Function::operator()(data_structures::List<int> &args) const {
        if (args.size() != argc)
            throw std::out_of_range("Bad number of function args");

        switch (type) {
            case Type::condition: {
                int cond = args.back();
                args.popBack();
                return cond > 0 ? args.back() : args.front();
            }
            case Type::negation:
                return -args.front();
            case Type::min: {
                int currentMin = args.front();
                args.popFront();
                while (!args.empty()) {
                    if (args.front() < currentMin)
                        currentMin = args.front();
                    args.popFront();
                }
                return currentMin;
            }
            case Type::max: {
                int currentMax = args.front();
                args.popFront();
                while (!args.empty()) {
                    if (args.front() > currentMax)
                        currentMax = args.front();
                    args.popFront();
                }
                return currentMax;
            }
        }
    }

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
            case TokenType::function: {
                const char *functionStr = symbol.token.function.str();
                stream << functionStr;
                delete[] functionStr;
                break;
            }
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
    }

    bool operator<(const Operation &o1, const Operation &o2) {
        return o1.prio() < o2.prio();
    }


    bool operator<=(const Operation &o1, const Operation &o2) {
        return o1.prio() <= o2.prio();
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
    }
}