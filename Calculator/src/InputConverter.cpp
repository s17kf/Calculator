//
// Created by stefan on 14/03/24.
//

#include "InputConverter.h"


using data_structures::Stack;

namespace calculator {
    void InputConverter::handleComma(Stack<Symbol *> &operatorStack) {
        Symbol *topSymbol = operatorStack.top();
        while (topSymbol->tokenType != TokenType::bracket) {
            // don't need to check bracket direction because only left brackets are added to operatorStack
            outputQueue.push(topSymbol);
            operatorStack.pop();
            topSymbol = operatorStack.top();
        }
    }

    void InputConverter::handleOperation(Stack<Symbol *> &operatorStack, Symbol *lastSymbol) {
        while (!operatorStack.empty()
               && operatorStack.top()->tokenType == TokenType::operation
               && lastSymbol->token.operation <= operatorStack.top()->token.operation) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
        }
        operatorStack.push(lastSymbol);
    }

    void InputConverter::handleRightBracket(Stack<Symbol *> &operatorStack) {
        Symbol *topSymbol = operatorStack.top();
        while (topSymbol->tokenType != TokenType::bracket) {
            // don't need to check bracket direction because only left brackets are added to operatorStack
            outputQueue.push(topSymbol);
            operatorStack.pop();
            topSymbol = operatorStack.top();
        }
        operatorStack.pop();
        delete topSymbol; // it is left bracket
        if (!operatorStack.empty()) {
            topSymbol = operatorStack.top();
            if (topSymbol->tokenType == TokenType::function) {
                outputQueue.push(topSymbol);
                operatorStack.pop();
            }
        }
    }

    void InputConverter::convertFormula() {
        Stack<Symbol *> operatorStack;
        Symbol *lastSymbol = inputReader.getNextSymbol();
        while (lastSymbol->tokenType != TokenType::end) {
            switch (lastSymbol->tokenType) {
                case TokenType::number:
                    outputQueue.push(lastSymbol);
                    break;
                case TokenType::operation:
                    handleOperation(operatorStack, lastSymbol);
                    break;
                case TokenType::function:
                    operatorStack.push(lastSymbol);
                    break;
                case TokenType::bracket:
                    if (lastSymbol->token.bracket.type == Bracket::Type::left) {
                        operatorStack.push(lastSymbol);
                    } else {
                        handleRightBracket(operatorStack);
                        delete lastSymbol;
                    };
                    break;
                case TokenType::comma:
                    handleComma(operatorStack);
                    delete lastSymbol;
                    break;
                case TokenType::end:
                    throw std::out_of_range("encountered EOF symbol ('.')");
            }
            lastSymbol = inputReader.getNextSymbol();
        }
        delete lastSymbol;
        while (!operatorStack.empty()) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();

        }
    }

    Symbol *InputConverter::removeNextSymbol() {
        Symbol *symbol = outputQueue.front();
        outputQueue.pop();
        return symbol;
    }

} // calculator