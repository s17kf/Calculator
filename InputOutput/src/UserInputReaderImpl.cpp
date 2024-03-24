//
// Created by stefan on 21/03/24.
//

#include "UserInputReaderImpl.h"

using data_structures::String;

namespace input_output {
    void UserInputReaderImpl::getNextSymbol(char *dest) {
        scanf("%s", dest);
    }
} // input_output