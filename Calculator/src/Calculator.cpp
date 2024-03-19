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
        while (inputConverter.symbolsLeft()) {
            Symbol *symbol = inputConverter.removeNextSymbol();
            switch (symbol->tokenType) {
                case TokenType::number:
                    stack.push(symbol->token->number);
                    delete symbol;
                    break;
                case TokenType::operation: {
                    printCurrentOperation(stack, symbol);
                    int a = stack.top();
                    stack.pop();
                    int b = stack.top();
                    stack.pop();
                    try {
                        stack.push((*symbol->token->operation)(a, b));
                    } catch (std::overflow_error &e) {
                        delete symbol;
                        while (inputConverter.symbolsLeft()){
                            delete inputConverter.removeNextSymbol();
                        }
//                        throw std::overflow_error(e.what());
                        return INT_MAX;
                    }
                    delete symbol;
                    break;
                }
                case TokenType::function: {
                    printCurrentOperation(stack, symbol);
                    unsigned int argc = symbol->token->function->argc;
                    List<int> args;
                    while (argc--) {
                        args.pushBack(stack.top());
                        stack.pop();
                    }
                    stack.push((*symbol->token->function)(args));
                    delete symbol;
                    break;
                }
                case TokenType::bracket:
                case TokenType::comma:
                case TokenType::end:
                    throw std::invalid_argument("Invalid argument during calculation");
            }
        }
        return stack.top();
    }

    void Calculator::handleUser(std::istream &istream, std::ostream &ostream) {
        unsigned int n;
        istream >> n;

        auto inputReader = InputReader(istream);
        auto calculator = Calculator(inputReader, ostream);

        for (unsigned int i = 0; i < n; ++i) {
            try {
                int result = calculator.calculate();
                if (result == INT_MAX) {
                    ostream << "ERROR" << std::endl;
                    continue;
                }
                ostream << result << std::endl;
            } catch ([[maybe_unused]] std::runtime_error &e) {
                ostream << "ERROR" << std::endl;
            }
        }
    }

} // calculator