//
// Created by stefan on 20/03/24.
//

#include "UserInputReaderStub.h"
#include <string>

using data_structures::String;

namespace input_output {
    data_structures::String UserInputReaderStub::getNextSymbol() {
        std::string s;
        stream >> s;
        return String(s.c_str());
    }

} // input_output