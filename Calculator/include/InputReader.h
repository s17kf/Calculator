//
// Created by stefan on 13/03/24.
//

#ifndef CALCULATORAADS_INPUTREADER_H
#define CALCULATORAADS_INPUTREADER_H

#include <iostream>


namespace calculator {
    struct Symbol;

    class InputReader {
    public:
        explicit InputReader(std::istream &inputStream) : inputStream(inputStream) {}

        Symbol *getNextSymbol();

    private:
        std::istream &inputStream;
    };

} // calculator

#endif //CALCULATORAADS_INPUTREADER_H
