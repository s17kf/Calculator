//
// Created by stefan on 19/03/24.
//

#include "LoggerStub.h"

#include <cstdio>
#include <cstdarg>

namespace input_output {
    int LoggerStub::log(Logger::Level level, const char *format, ...) {
        if (level < logLevel) {
            return 0;
        }
        char buffer[BUF_SIZE];
        va_list args;
        va_start(args, format);
        int result = vsnprintf(buffer, BUF_SIZE, format, args);
        va_end(args);
        stream << buffer;
        return result;
    }

    void LoggerStub::setLogLevel(Logger::Level level) {
        logLevel = level;
    }

    void LoggerStub::reset() {
        stream.str("");
    }

    std::string LoggerStub::str() const {
        return stream.str();
    }
} // input_output