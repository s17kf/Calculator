//
// Created by stefan on 14/03/24.
//

#include "Calculator.h"

#include "Stack.h"
#include "List.h"

using data_structures::Stack;
using data_structures::List;

namespace calculator {

    int Calculator::calculate() {
        Stack<int> stack;
        inputConverter.convertFormula();
        inputConverter.printOutputQueue(ostream);
        uint loopCounter = 0;
        while (inputConverter.symbolsLeft()) {
            Symbol *symbol = inputConverter.removeNextSymbol();
            switch (symbol->tokenType) {
                case TokenType::number:
                    stack.push(symbol->token.number);
                    delete symbol;
                    break;
                case TokenType::operation: {
                    printCurrentOperation(stack, symbol);
                    int a = stack.top();
                    stack.pop();
                    int b = stack.top();
                    stack.pop();
                    try {
                        stack.push(symbol->token.operation(a, b));
                    } catch (std::overflow_error &e) {
                        delete symbol;
                        throw e;
                    }
                    delete symbol;
                    break;
                }
                case TokenType::function: {
                    printCurrentOperation(stack, symbol);
                    uint argc = symbol->token.function.argc;
                    List<int> args;
                    while (argc--) {
                        args.pushBack(stack.top());
                        stack.pop();
                    }
                    stack.push(symbol->token.function(args));
                    delete symbol;
                    break;
                }
                case TokenType::bracket:
                case TokenType::comma:
                case TokenType::end:
                    throw std::invalid_argument("Invalid argument during calculation");
            }
            ++loopCounter;
        }
        return stack.top();
    }

} // calculator