//
// Created by stefan on 20/03/24.
//

#ifndef CALCULATORAADS_USERINPUTREADERSTUB_H
#define CALCULATORAADS_USERINPUTREADERSTUB_H

#include "UserInputReader.h"

#include <sstream>

namespace input_output {

    class UserInputReaderStub : public UserInputReader {
    public:
        UserInputReaderStub(const std::string str) : stream(str) {}

        UserInputReaderStub() {};

        void setInputString(std::string s) { stream.str(s); }

        void getNextSymbol(char *dest) override;

        ~UserInputReaderStub() override = default;

    private:
        std::stringstream stream;
    };

} // input_output

#endif //CALCULATORAADS_USERINPUTREADERSTUB_H
