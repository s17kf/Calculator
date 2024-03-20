//
// Created by stefan on 19/03/24.
//

#ifndef CALCULATORAADS_LOGGER_H
#define CALCULATORAADS_LOGGER_H

namespace input_output {

    class Logger {
    public:
        enum class Level {
            low,
            medium,
            high,
        };

        virtual int log(Logger::Level level, const char *format, ...) = 0;

        virtual ~Logger() = default;
    };

} // input_output

#endif //CALCULATORAADS_LOGGER_H
