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
                return new Symbol(TokenType::end, new Token('.'));
            case ',':
                return new Symbol(TokenType::comma, new Token(','));
            case '+':
                return new Symbol(TokenType::operation,
                                  new Token(new Operation(Operation::Type::addition)));
            case '-':
                return new Symbol(TokenType::operation,
                                  new Token(new Operation(Operation::Type::subtraction)));
            case '*':
                return new Symbol(TokenType::operation,
                                  new Token(new Operation(Operation::Type::multiplying)));
            case '/':
                return new Symbol(TokenType::operation,
                                  new Token(new Operation(Operation::Type::division)));
            case '(':
                return new Symbol(TokenType::bracket,
                                  new Token(new Bracket(Bracket::Type::left)));
            case ')':
                return new Symbol(TokenType::bracket,
                                  new Token(new Bracket(Bracket::Type::right)));
            case 'N':
                if (strcmp(input, "N") == 0)
                    return new Symbol(TokenType::function,
                                      new Token(new Function(Function::Type::negation)));
            case 'I':
                if (strcmp(input, "IF") == 0)
                    return new Symbol(TokenType::function,
                                      new Token(new Function(Function::Type::condition)));
            case 'M':
                if (strcmp(input, "MIN") == 0)
                    return new Symbol(TokenType::function,
                                      new Token(new Function(Function::Type::min)));
                else if (strcmp(input, "MAX") == 0)
                    return new Symbol(TokenType::function,
                                      new Token(new Function(Function::Type::max)));
            default: {
                int number;
                sscanf(input, "%d",&number);
                return new Symbol(TokenType::number,
                                  new Token(number));
            }
        }
    }

} // calculator