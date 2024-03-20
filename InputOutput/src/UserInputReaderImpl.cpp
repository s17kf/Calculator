//
// Created by stefan on 21/03/24.
//

#include "UserInputReaderImpl.h"

using data_structures::String;

namespace input_output {
    data_structures::String UserInputReaderImpl::getNextSymbol() {
        char buffer[10];
        scanf("%s", buffer);
        return String(buffer);
    }
} // input_output