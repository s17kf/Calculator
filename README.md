# Calculator

This project was developed for academic purposes as part of the Algorithms and Data Structures course at Gdańsk University of Technology.

## Description

The calculator is capable of performing basic arithmetic operations (+, -, *, /) with standard mathematical priority, supporting parentheses '(...)', and the following additional functions:
- IF(a, b, c): if a > 0, return b; otherwise return c.
- N a: unary negation, i.e., -a.
- MIN(a1, a2, ...), MAX(a1, a2, ...): functions MIN and MAX have no restriction on the number of parameters.

The program reads input formulas in infix notation, converts them into postfix notation, and performs the calculations.
The conversion into postfix notation is done on the fly - the infix notation formula is not stored, and each token is read from input only once.

### Input
- n: number of formulas
- n formulas, each in the following form:

Each formula is a valid expression in an infix notation with functions and ends with a dot ('.'). Each token is separated by some whitespace characters.
Each operand is a positive integer (although the result of an operation might be negative).
Each operator is a single character and every function name consists only of capital letters.

### Output (verbose)
- The formula in postfix notation
- Before executing each operation, the operator or function and the content of the stack are printed
- The final result or 'ERROR' (printed when division by 0 is encountered)

### Output (silent)
- The final result or 'ERROR'

## Note
Silent mode is enabled by defining 'SILENT' in the Calculator.h file.
This is because of the way the project is evaluated - there is no way to use any argument, only the main function is run.
