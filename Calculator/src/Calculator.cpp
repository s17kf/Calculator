//
// Created by stefan on 14/03/24.
//

#include "Calculator.h"

#include <charconv>

#include "List.h"
#include "Logger.h"
#include "String.h"

using data_structures::Stack;
using data_structures::List;
using data_structures::String;

using input_output::Logger;
using input_output::UserInputReader;

namespace calculator {

    void Calculator::execOperation(Operation &operation, Stack<int> &stack) {
        auto a = stack.pop();
        auto b = stack.pop();
        stack.push(operation(a, b));
    }

    void Calculator::handleNegationsFromTopOfStack(Stack<Symbol *> &operatorStack, Stack<int> &resultStack) {
        while (!operatorStack.empty() &&
               operatorStack.top()->tokenType == TokenType::function &&
               operatorStack.top()->token.function.type == Function::Type::negation) {
            resultStack.push(-resultStack.pop());
            delete operatorStack.pop();
        }
    }

    void Calculator::handleFunction(Symbol *functionSymbol, Stack<int> &resultStack) {
        unsigned int argc = functionSymbol->token.function.argc;
        switch (functionSymbol->token.function.type) {
            case Function::Type::condition: {
                int c = resultStack.pop();
                int b = resultStack.pop();
                int a = resultStack.pop();
                resultStack.push(a > 0 ? b : c);
                break;
            }
            case Function::Type::negation:
                resultStack.push(-resultStack.pop());
                break;
            case Function::Type::min: {
                int currentMin = resultStack.pop();
                while (--argc) {
                    if (resultStack.top() < currentMin)
                        currentMin = resultStack.top();
                    resultStack.pop();
                }
                resultStack.push(currentMin);
                break;
            }
            case Function::Type::max: {
                int currentMax = resultStack.pop();
                while (--argc) {
                    if (resultStack.top() > currentMax)
                        currentMax = resultStack.top();
                    resultStack.pop();
                }
                resultStack.push(currentMax);
                break;
            }
        }
    }

    Result Calculator::calculate() {
        Stack<int> stack;
        mInputConverter.convertFormula();
#ifndef SILENT
        mInputConverter.printOutputQueue(mLogger);
#endif
        while (mInputConverter.symbolsLeft()) {
            Symbol *symbol = mInputConverter.removeNextSymbol();
            switch (symbol->tokenType) {
                case TokenType::number:
                    stack.push(symbol->token.number);
                    delete symbol;
                    break;
                case TokenType::operation: {
#ifndef SILENT
                    printCurrentOperation(stack, symbol);
#endif
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
#ifndef SILENT
                    printCurrentOperation(stack, symbol);
#endif
                    handleFunction(symbol, stack);
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

    Result Calculator::silentCalculate() {
        Stack<Symbol *> operatorStack;
        Stack<unsigned int *> argumentCounters;
        Stack<int> resultStack;
        Symbol *lastSymbol = mInputReader.getNextSymbol();
        size_t symbolCounter = 0;
        while (lastSymbol->tokenType != TokenType::end) {
            ++symbolCounter;
            switch (lastSymbol->tokenType) {
                case TokenType::number:
                    resultStack.push(lastSymbol->token.number);
                    delete lastSymbol;
                    handleNegationsFromTopOfStack(operatorStack, resultStack);
                    break;
                case TokenType::operation: {
                    while (!operatorStack.empty() &&
                           operatorStack.top()->tokenType == TokenType::operation &&
                           lastSymbol->token.operation.prio() <= operatorStack.top()->token.operation.prio()) {
                        Symbol *operationToExec = operatorStack.pop();
                        try {
                            execOperation(operationToExec->token.operation, resultStack);
                        } catch (std::overflow_error &e) {
                            delete lastSymbol;
                            delete operationToExec;
                            while (!operatorStack.empty())
                                delete operatorStack.pop();
                            mInputReader.wasteRestOfFormula();
                            return {Result::Status::error, 0};
                        }
                        delete operationToExec;
                    }
                    operatorStack.push(lastSymbol);
                    break;
                }
                case TokenType::function:
                    operatorStack.push(lastSymbol);
                    if (lastSymbol->token.function.type != Function::Type::negation) {
                        argumentCounters.push(&lastSymbol->token.function.argc);
                    }
                    break;
                case TokenType::bracket:
                    if (lastSymbol->token.bracket.type == Bracket::Type::left) {
                        operatorStack.push(lastSymbol);
                    } else {
                        while (operatorStack.top()->tokenType != TokenType::bracket) {
                            // don't need to check bracket direction because only left brackets are added to operatorStack
                            if (operatorStack.top()->tokenType == TokenType::operation) {
                                Symbol *operationToExec = operatorStack.pop();
                                try {
                                    execOperation(operationToExec->token.operation, resultStack);
                                } catch (std::overflow_error &e) {
                                    delete lastSymbol;
                                    delete operationToExec;
                                    while (!operatorStack.empty())
                                        delete operatorStack.pop();
                                    mInputReader.wasteRestOfFormula();
                                    return {Result::Status::error, 0};
                                }
                                delete operationToExec;
                            } else {
                                // it has to be negation as its only function which doesn't need brackets
                                delete operatorStack.pop();
                                resultStack.push(-resultStack.pop());
                            }
                        }
                        delete operatorStack.pop();
                        if (!operatorStack.empty() && operatorStack.top()->tokenType == TokenType::function) {
                            handleFunction(operatorStack.top(), resultStack);
                            if (operatorStack.top()->token.function.type != Function::Type::negation) {
                                argumentCounters.pop();
                            }
                            delete operatorStack.pop();
                        }
                        handleNegationsFromTopOfStack(operatorStack, resultStack);
                        delete lastSymbol;
                    };
                    break;
                case TokenType::comma: {
                    Symbol *symbolToHandle = operatorStack.top();
                    while (symbolToHandle->tokenType != TokenType::bracket) {
                        if (symbolToHandle->tokenType == TokenType::operation) {
                            try {
                                execOperation(symbolToHandle->token.operation, resultStack);
                            } catch (std::overflow_error &e) {
                                delete lastSymbol;
                                while (!operatorStack.empty())
                                    delete operatorStack.pop();
                                mInputReader.wasteRestOfFormula();
                                return {Result::Status::error, 0};
                            }
                        } else if (symbolToHandle->tokenType == TokenType::function) {
                            // it has to be negation as its only function which doesn't need brackets
                            resultStack.push(-resultStack.pop());
                        }
                        delete symbolToHandle;
                        operatorStack.pop();
                        symbolToHandle = operatorStack.top();
                    }
                    if (!argumentCounters.empty())
                        ++(*argumentCounters.top());
                    delete lastSymbol;
                    break;
                }
                case TokenType::end:
                    throw std::out_of_range("encountered EOF symbol ('.')");
            }
            lastSymbol = mInputReader.getNextSymbol();
        }
        delete lastSymbol;
        while (!operatorStack.empty()) {
            // missing check of symbol's type as only operations should left on stack at this point
            try {
                execOperation(operatorStack.top()->token.operation, resultStack);
            } catch (std::overflow_error &e) {
                while (!operatorStack.empty())
                    delete operatorStack.pop();
                return {Result::Status::error, 0};
            }
            delete operatorStack.pop();
        }
        return {Result::Status::success, resultStack.top()};
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
#ifndef SILENT
                auto result = calculator.calculate();
#else
                auto result = calculator.silentCalculate();
#endif
                if (result.status != Result::Status::success) {
                    logger.log("ERROR\n");
                    continue;
                }
                logger.log("%d\n", result.value);
            } catch ([[maybe_unused]] std::exception &e) {
                logger.log("Calculator error %s\n", e.what());
            }
        }
    }

    void Calculator::printCurrentOperation(Stack<int> &stack, Symbol *operation) {
        mLogger.log(operation->str().c_str());
        for (const auto &item: stack) {
            mLogger.log(" %d", item);
        }
        mLogger.log("\n");
    }

} // calculator