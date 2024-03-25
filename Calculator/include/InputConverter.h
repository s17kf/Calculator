//
// Created by stefan on 14/03/24.
//

#ifndef CALCULATORAADS_INPUTCONVERTER_H
#define CALCULATORAADS_INPUTCONVERTER_H

#include "InputReader.h"
#include "Queue.h"
#include "Stack.h"
#include "Symbol.h"
#include "Logger.h"

namespace calculator {

    class InputConverter {
    public:
        explicit InputConverter(InputReader &inputReader) : inputReader(inputReader) {}

        ~InputConverter() {
            while (!outputQueue.empty()) {
                delete outputQueue.pop();
            }
        }

        void convertFormula();

        Symbol *removeNextSymbol();

        [[nodiscard]] bool symbolsLeft() const { return !outputQueue.empty(); }

        void printOutputQueue(input_output::Logger &logger);

    private:
        void handleComma(data_structures::Stack<Symbol *> &operatorStack);

        void handleOperation(data_structures::Stack<Symbol *> &operatorStack, Symbol *lastSymbol);

        void handleRightBracket(data_structures::Stack<Symbol *> &operatorStack,
                                data_structures::Stack<unsigned int *> &argumentCounters);

        void moveNegationsFromTopOfStackToOutput(data_structures::Stack<Symbol *> &operatorStack);

        InputReader inputReader;
        data_structures::Queue<Symbol *> outputQueue;
    };

} // calculator

#endif //CALCULATORAADS_INPUTCONVERTER_H
