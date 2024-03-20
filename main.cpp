#include <iostream>
#include "Calculator.h"
#include "ConsoleLogger.h"

using input_output::ConsoleLogger;
using input_output::Logger;

int main() {
    ConsoleLogger logger(Logger::Level::medium);
    calculator::Calculator::handleUser(std::cin, logger);

    return 0;
}
