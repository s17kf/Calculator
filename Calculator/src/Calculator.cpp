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
                    int a = stack.top();
                    stack.pop();
                    int b = stack.top();
                    stack.pop();
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
                    List<int> args;
                    while (argc--) {
                        args.pushBack(stack.top());
                        stack.pop();
                    }
                    stack.push((symbol->token.function)(args));
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
        String nStr = userInputReader.getNextSymbol();
        std::from_chars(nStr.c_str(), nStr.c_str() + nStr.size(), n);

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