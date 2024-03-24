//
// Created by stefan on 14/03/24.
//

#include "InputConverter.h"

using data_structures::Stack;
using input_output::Logger;

namespace calculator {
    void InputConverter::handleComma(Stack<Symbol *> &operatorStack) {
        while (operatorStack.top()->tokenType != TokenType::bracket) {
            // don't need to check bracket direction because only left brackets are added to operatorStack
            outputQueue.push(operatorStack.pop());
        }
    }

    void InputConverter::handleOperation(Stack<Symbol *> &operatorStack, Symbol *lastSymbol) {
        while (!operatorStack.empty() &&
               operatorStack.top()->tokenType == TokenType::operation &&
               lastSymbol->token.operation.prio() <= operatorStack.top()->token.operation.prio()) {
            outputQueue.push(operatorStack.pop());
        }
        operatorStack.push(lastSymbol);
    }

    void InputConverter::handleRightBracket(Stack<Symbol *> &operatorStack, Stack<unsigned int *> &argumentCounters) {
        while (operatorStack.top()->tokenType != TokenType::bracket) {
            // don't need to check bracket direction because only left brackets are added to operatorStack
            outputQueue.push(operatorStack.pop());
        }
        delete operatorStack.pop(); // it is left bracket
        if (!operatorStack.empty()) {
            if (operatorStack.top()->tokenType == TokenType::function) {
                if (operatorStack.top()->token.function.type != Function::Type::negation)
                    argumentCounters.pop();
                outputQueue.push(operatorStack.pop());
            }
        }
    }


    void InputConverter::moveNegationsFromTopOfStackToOutput(Stack<Symbol *> &operatorStack) {
        while (!operatorStack.empty() &&
               operatorStack.top()->tokenType == TokenType::function &&
               operatorStack.top()->token.function.type == Function::Type::negation) {
            outputQueue.push(operatorStack.pop());
        }
    }

    void InputConverter::printOutputQueue(Logger &logger) {
        auto it = outputQueue.begin();
        logger.log((*it++)->str().c_str());
        for (; it != outputQueue.end(); ++it) {
            logger.log("  %s", (*it)->str().c_str());
        }
        logger.log("\n");
    }

    void InputConverter::convertFormula() {
        Stack<Symbol *> operatorStack;
        Stack<unsigned int *> argumentCounters;
        Symbol *lastSymbol = inputReader.getNextSymbol();
        while (lastSymbol->tokenType != TokenType::end) {
            switch (lastSymbol->tokenType) {
                case TokenType::number:
                    outputQueue.push(lastSymbol);
                    moveNegationsFromTopOfStackToOutput(operatorStack);
                    break;
                case TokenType::operation:
                    handleOperation(operatorStack, lastSymbol);
                    break;
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
                        handleRightBracket(operatorStack, argumentCounters);
                        moveNegationsFromTopOfStackToOutput(operatorStack);
                        delete lastSymbol;
                    };
                    break;
                case TokenType::comma:
                    handleComma(operatorStack);
                    if (!argumentCounters.empty()) {
                        ++(*argumentCounters.top());
                    }
                    delete lastSymbol;
                    break;
                case TokenType::end:
                    throw std::out_of_range("encountered EOF symbol ('.')");
            }
            lastSymbol = inputReader.getNextSymbol();
        }
        delete lastSymbol;
        while (!operatorStack.empty()) {
            outputQueue.push(operatorStack.pop());

        }
    }

    Symbol *InputConverter::removeNextSymbol() {
        return outputQueue.pop();;
    }

} // calculator