#! /usr/bin/bash

dst_dir="filesToEvaluation"

files_to_cp=(
"main.cpp"

"DataStructures/include/List.h"
"DataStructures/include/Queue.h"
"DataStructures/include/Stack.h"
"DataStructures/include/String.h"
"DataStructures/src/String.cpp"

"Calculator/include/Calculator.h"
"Calculator/include/InputConverter.h"
"Calculator/include/InputReader.h"
"Calculator/include/Symbol.h"
"Calculator/src/Calculator.cpp"
"Calculator/src/InputConverter.cpp"
"Calculator/src/InputReader.cpp"
"Calculator/src/Symbol.cpp"

"InputOutput/include/ConsoleLogger.h"
"InputOutput/include/Logger.h"
"InputOutput/include/UserInputReader.h"
"InputOutput/include/UserInputReaderImpl.h"
"InputOutput/src/ConsoleLogger.cpp"
"InputOutput/src/UserInputReaderImpl.cpp")

for file in "${files_to_cp[@]}"; do
  cp "$file" "$dst_dir"
done
