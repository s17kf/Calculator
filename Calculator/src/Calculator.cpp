//
// Created by stefan on 14/03/24.
//

#include "Calculator.h"

#include <charconv>

#include "Stack.h"
#include "List.h"
#include "Logger.h"
#include "String.h"

using data_structures::Stack;
using data_structures::List;
using data_structures::String;

using input_output::Logger;
using input_output::UserInputReader;

namespace calculator {

    Result Calculator::calculate() {
        Stack<int> stack;
        mInputConverter.convertFormula();
        mInputConverter.printOutputQueue(mLogger);
        while (mInputConverter.symbolsLeft()) {
            Symbol *symbol = mInputConverter.removeNextSymbol();
            switch (symbol->tokenType) {
                case TokenType::number:
                    stack.push(symbol->token.number);
                    delete symbol;
                    break;
                case TokenType::operation: {
                    printCurrentOperation(stack, symbol);
                    int a = stack.pop();
                    int b = stack.pop();
                    try {
                        stack.push(symbol->token.operation(a, b));
                    } catch (std::overflow_error &e) {
                        delete symbol;
                        while (mInputConverter.symbolsLeft()) {
                            delete mInputConverter.removeNextSymbol();
                        }
//                        throw std::overflow_error(e.what());
                        return {Result::Status::error, 0};
                    }
                    delete symbol;
                    break;
                }
                case TokenType::function: {
                    printCurrentOperation(stack, symbol);
                    unsigned int argc = symbol->token.function.argc;
                    switch (symbol->token.function.type) {
                        case Function::Type::condition: {
                            int c = stack.pop();
                            int b = stack.pop();
                            int a = stack.pop();
                            stack.push(a > 0 ? b : c);
                            break;
                        }
                        case Function::Type::negation:
                            stack.push(-stack.pop());
                            break;
                        case Function::Type::min: {
                            int currentMin = stack.pop();
                            while (--argc) {
                                if (stack.top() < currentMin)
                                    currentMin = stack.top();
                                stack.pop();
                            }
                            stack.push(currentMin);
                            break;
                        }
                        case Function::Type::max: {
                            int currentMax = stack.pop();
                            while (--argc) {
                                if (stack.top() > currentMax)
                                    currentMax = stack.top();
                                stack.pop();
                            }
                            stack.push(currentMax);
                            break;
                        }
                    }
                    delete symbol;
                    break;
                }
                case TokenType::bracket:
                case TokenType::comma:
                case TokenType::end:
                    throw std::invalid_argument("Invalid argument during calculation");
            }
        }
        return {Result::Status::success, stack.top()};
    }

    void Calculator::handleUser(UserInputReader &userInputReader, Logger &logger) {
        int n;
        char nStr[10];
        userInputReader.getNextSymbol(nStr);
        std::from_chars(nStr, nStr + strlen(nStr), n);

        auto inputReader = InputReader(userInputReader);
        auto calculator = Calculator(inputReader, logger);

        for (unsigned int i = 0; i < n; ++i) {
            try {
                auto result = calculator.calculate();
                if (result.status != Result::Status::success) {
                    logger.log(Logger::Level::high, "ERROR\n");
                    continue;
                }
                logger.log(Logger::Level::high, "%d\n", result.value);
            } catch ([[maybe_unused]] std::exception &e) {
                logger.log(Logger::Level::high, "Calculator error\n");
            }
        }
    }

    void Calculator::printCurrentOperation(Stack<int> &stack, Symbol *operation) {
        mLogger.log(Logger::Level::medium, operation->str().c_str());
        for (const auto &item: stack) {
            mLogger.log(Logger::Level::medium, " %d", item);
        }
        mLogger.log(Logger::Level::medium, "\n");
    }

} // calculator