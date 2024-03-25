#include "Calculator.h"
#include "ConsoleLogger.h"

#include "UserInputReaderImpl.h"

using input_output::ConsoleLogger;
using input_output::Logger;
using input_output::UserInputReaderImpl;

int main() {
    ConsoleLogger logger;
    UserInputReaderImpl userInputReader;

    calculator::Calculator::handleUser(userInputReader, logger);

    return 0;
}
