//
// Created by stefan on 14/03/24.
//

#ifndef CALCULATORAADS_INPUTCONVERTER_H
#define CALCULATORAADS_INPUTCONVERTER_H

#include "InputReader.h"
#include "Queue.h"
#include "Stack.h"
#include "Symbol.h"

#include "QueueVector.h"
#include "StackVector.h"


namespace calculator {

    class InputConverter {
    public:
        explicit InputConverter(InputReader &inputReader) : inputReader(inputReader) {}

        void convertFormula();

        Symbol *removeNextSymbol();

        bool symbolsLeft() { return !outputQueue.empty(); }

    private:
        void handleComma(data_structures::Stack<Symbol *> &operatorStack);

        void handleOperation(data_structures::Stack<Symbol *> &operatorStack, Symbol *lastSymbol);

        void handleRightBracket(data_structures::Stack<Symbol *> &operatorStack,
                                data_structures::Stack<uint *> &argumentCounters);

        void moveNegationsFromTopOfStackToOutput(data_structures::Stack<Symbol *> &operatorStack);

        InputReader inputReader;
        data_structures::Queue<Symbol *> outputQueue;
    };

} // calculator

#endif //CALCULATORAADS_INPUTCONVERTER_H
