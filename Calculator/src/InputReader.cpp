//
// Created by stefan on 13/03/24.
//

#include <cstring>
#include <charconv>

#include "InputReader.h"
#include "Symbol.h"
#include "String.h"

using data_structures::String;

namespace calculator {

    Symbol *InputReader::getNextSymbol() {
        char input[10];
        userInputReader.getNextSymbol(input);
        switch (input[0]) {
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
                return new Symbol(TokenType::function, Function(Function::Type::negation));
            case 'I':
                return new Symbol(TokenType::function, Function(Function::Type::condition));
            case 'M':
                if (input[1] == 'I')
                    return new Symbol(TokenType::function, Function(Function::Type::min));
                else if (input[1] == 'A')
                    return new Symbol(TokenType::function, Function(Function::Type::max));
            default: {
                int number;
                std::from_chars(input, input + strlen(input), number);
                return new Symbol(TokenType::number, number);
            }
        }
    }

} // calculator