//
// Created by stefan on 21/03/24.
//

#ifndef CALCULATORAADS_USERINPUTREADERIMPL_H
#define CALCULATORAADS_USERINPUTREADERIMPL_H

#include "UserInputReader.h"

namespace input_output {

    class UserInputReaderImpl : public UserInputReader {
    public:
        data_structures::String getNextSymbol() override;

        ~UserInputReaderImpl() override = default;
    };

} // input_output

#endif //CALCULATORAADS_USERINPUTREADERIMPL_H
