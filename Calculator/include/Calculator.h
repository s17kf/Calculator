//
// Created by stefan on 14/03/24.
//

#ifndef CALCULATORAADS_CALCULATOR_H
#define CALCULATORAADS_CALCULATOR_H

#include <ostream>

#include "InputReader.h"
#include "Queue.h"
#include "Stack.h"
#include "InputConverter.h"

namespace calculator {

    class Calculator {
    public:
        explicit Calculator(InputReader &inputReader, std::ostream &ostream = std::cout) :
                inputConverter(inputReader),
                ostream(ostream) {}

        int calculate();

    private:
        inline void printCurrentOperation(data_structures::Stack<int> &stack, Symbol *operation) {
            ostream << *operation;
            for (const auto &item: stack) {
                ostream << " " << item;
            }
            ostream << std::endl;
        }

        InputConverter inputConverter;
        std::ostream &ostream;
    };

} // calculator

#endif //CALCULATORAADS_CALCULATOR_H
