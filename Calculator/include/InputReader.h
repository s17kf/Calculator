//
// Created by stefan on 13/03/24.
//

#ifndef CALCULATORAADS_INPUTREADER_H
#define CALCULATORAADS_INPUTREADER_H

#include "UserInputReader.h"


namespace calculator {
    struct Symbol;

    class InputReader {
    public:
        explicit InputReader(input_output::UserInputReader &userInputReader) : userInputReader(userInputReader) {}

        Symbol *getNextSymbol();

    private:
        input_output::UserInputReader &userInputReader;
    };

} // calculator

#endif //CALCULATORAADS_INPUTREADER_H
