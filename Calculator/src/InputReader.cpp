//
// Created by stefan on 13/03/24.
//

#include <cstring>

#include "InputReader.h"
#include "Symbol.h"
#include "String.h"

using data_structures::String;

namespace calculator {

    Symbol *InputReader::getNextSymbol() {
        String input = userInputReader.getNextSymbol();
        switch (input.c_str()[0]) {
            case '.':
                return new Symbol(TokenType::end, '.');
            case ',':
                return new Symbol(TokenType::comma, ',');
            case '+':
                return new Symbol(TokenType::operation, Operation(Operation::Type::addition));
            case '-':
                return new Symbol(TokenType::operation, Operation(Operation::Type::subtraction));
            case '*':
                return new Symbol(TokenType::operation, Operation(Operation::Type::multiplying));
            case '/':
                return new Symbol(TokenType::operation, Operation(Operation::Type::division));
            case '(':
                return new Symbol(TokenType::bracket, Bracket(Bracket::Type::left));
            case ')':
                return new Symbol(TokenType::bracket, Bracket(Bracket::Type::right));
            case 'N':
                if (strcmp(input.c_str(), "N") == 0)
                    return new Symbol(TokenType::function, Function(Function::Type::negation));
            case 'I':
                if (strcmp(input.c_str(), "IF") == 0)
                    return new Symbol(TokenType::function, Function(Function::Type::condition));
            case 'M':
                if (strcmp(input.c_str(), "MIN") == 0)
                    return new Symbol(TokenType::function, Function(Function::Type::min));
                else if (strcmp(input.c_str(), "MAX") == 0)
                    return new Symbol(TokenType::function, Function(Function::Type::max));
            default: {
                int number;
                // TODO: use from_chars
                sscanf(input.c_str(), "%d", &number);
                return new Symbol(TokenType::number, number);
            }
        }
    }

} // calculator