//
// Created by stefan on 20/03/24.
//

#include "UserInputReaderStub.h"
#include <string>

using data_structures::String;

namespace input_output {

    void UserInputReaderStub::getNextSymbol(char *dest) {
        std::string s;
        stream >> s;
        strcpy(dest, s.c_str());
    }

} // input_output