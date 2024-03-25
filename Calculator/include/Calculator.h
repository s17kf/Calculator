//
// Created by stefan on 14/03/24.
//

#ifndef CALCULATORAADS_CALCULATOR_H
#define CALCULATORAADS_CALCULATOR_H

#include <iostream>

#include "InputReader.h"
#include "Queue.h"
#include "Stack.h"
#include "InputConverter.h"
#include "Logger.h"
#include "UserInputReader.h"

//#define SILENT

namespace calculator {

    struct Result {
        enum class Status {
            success,
            error,
        };

        Result(Status status, int value) : status(status), value(value) {}

        Status status;
        int value;
    };

    class Calculator {
    public:
        explicit Calculator(InputReader &inputReader, input_output::Logger &logger) :
                mInputConverter(inputReader),
                mLogger(logger) {}

        Result calculate();

        static void handleUser(input_output::UserInputReader &userInputReader, input_output::Logger &logger);

    private:
        inline void printCurrentOperation(data_structures::Stack<int> &stack, Symbol *operation);

        InputConverter mInputConverter;
        input_output::Logger &mLogger;
    };

} // calculator

#endif //CALCULATORAADS_CALCULATOR_H
