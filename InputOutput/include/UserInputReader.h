//
// Created by stefan on 21/03/24.
//

#ifndef CALCULATORAADS_USERINPUTREADER_H
#define CALCULATORAADS_USERINPUTREADER_H

#include "String.h"

namespace input_output {

    class UserInputReader {
    public:
        virtual data_structures::String getNextSymbol() = 0;

        virtual ~UserInputReader() = default;
    };

} // input_output

#endif //CALCULATORAADS_USERINPUTREADER_H
