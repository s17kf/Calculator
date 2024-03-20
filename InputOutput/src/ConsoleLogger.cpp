//
// Created by stefan on 19/03/24.
//

#include <cstdarg>
#include <cstdio>

#include "ConsoleLogger.h"

namespace input_output {
    int ConsoleLogger::log(Logger::Level level, const char *format, ...) {
        if (level < logLevel) {
            return 0;
        }
        va_list args;
        va_start(args, format);
        int result = vprintf(format, args);
        va_end(args);
        return result;
    }

} // input_output
