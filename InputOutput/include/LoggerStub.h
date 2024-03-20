//
// Created by stefan on 19/03/24.
//

#ifndef CALCULATORAADS_LOGGERSTUB_H
#define CALCULATORAADS_LOGGERSTUB_H

#include "Logger.h"

#include <sstream>

namespace input_output {

    class LoggerStub : public Logger {
    public:
        int log(Logger::Level level, const char *format, ...) override;

        void setLogLevel(Level level) override;

        void reset();

        std::string str() const;

        ~LoggerStub() = default;

    private:
        const size_t BUF_SIZE = 200;
        std::stringstream stream;
        Level logLevel;
    };

} // input_output

#endif //CALCULATORAADS_LOGGERSTUB_H
