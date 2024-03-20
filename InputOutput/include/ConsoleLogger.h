//
// Created by stefan on 19/03/24.
//

#ifndef CALCULATORAADS_CONSOLELOGGER_H
#define CALCULATORAADS_CONSOLELOGGER_H

#include "Logger.h"

namespace input_output {

    class ConsoleLogger : public Logger {
    public:
        explicit ConsoleLogger(Level level) : logLevel(level) {}

        int log(Logger::Level level, const char *format, ...) override;

        ~ConsoleLogger() override = default;

    private:
        Level logLevel;
    };

} // input_output

#endif //CALCULATORAADS_CONSOLELOGGER_H
