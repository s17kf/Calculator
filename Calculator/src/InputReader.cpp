//
// Created by stefan on 13/03/24.
//

#include <cstring>

#include "InputReader.h"
#include "Symbol.h"

namespace calculator {

    Symbol *InputReader::getNextSymbol() {
        char input[11];
        inputStream >> input;
        switch (input[0]) {
            case '.':
                return new Symbol{.tokenType=TokenType::end};
            case ',':
                return new Symbol{.tokenType=TokenType::comma};
            case '+':
                return new Symbol{.tokenType = TokenType::operation,
                        .token={.operation={.type=Operation::Type::addition}}};
            case '-':
                return new Symbol{.tokenType = TokenType::operation,
                        .token={.operation={.type=Operation::Type::subtraction}}};
            case '*':
                return new Symbol{.tokenType = TokenType::operation,
                        .token={.operation={.type=Operation::Type::multiplying}}};
            case '/':
                return new Symbol{.tokenType = TokenType::operation,
                        .token={.operation={.type=Operation::Type::division}}};
            case '(':
                return new Symbol{.tokenType = TokenType::bracket,
                        .token = {.bracket={.type=Bracket::Type::left}}};
            case ')':
                return new Symbol{.tokenType = TokenType::bracket,
                        .token = {.bracket={.type=Bracket::Type::right}}};
            case 'N':
                if (strcmp(input, "N") == 0)
                    return new Symbol{.tokenType = TokenType::function,
                            .token = {.function={.type=Function::Type::negation,
                                    .argc=0}}};
                break;
            case 'I':
                if (strcmp(input, "IF") == 0)
                    return new Symbol{.tokenType = TokenType::function,
                            .token = {.function={.type=Function::Type::condition,
                                    .argc=3}}};
                break;
            case 'M':
                if (strcmp(input, "MIN") == 0)
                    return new Symbol{.tokenType = TokenType::function,
                            .token = {.function={.type=Function::Type::min,
                                    .argc=0}}};
                else if (strcmp(input, "MAX") == 0)
                    return new Symbol{.tokenType = TokenType::function,
                            .token = {.function={.type=Function::Type::max,
                                    .argc=0}}};
                break;
            default:
                return new Symbol{.tokenType = TokenType::number,
                        .token = {.number=std::stoi(input)}};
        }
        throw std::invalid_argument(std::string("Invalid symbol: ") + input);

    }

} // calculator