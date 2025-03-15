# Lexical Analyzer From Prof.Yu

## Token Types

| Token Type | Value | Description |
|------------|-------|-------------|
| CONSTANT   | 1     | Numerical constants, character literals, and string literals |
| IDENTIFIER | 2     | Variable and function names |
| INT        | 3     | 'int' keyword |
| DOUBLE     | 4     | 'double' keyword |
| LONG       | 5     | 'long' keyword |
| FLOAT      | 6     | 'float' keyword |
| CHAR       | 7     | 'char' keyword |
| BOOL       | 8     | 'bool' keyword |
| STRING     | 9     | 'string' keyword |
| IF         | 10    | 'if' keyword |
| ELSE       | 11    | 'else' keyword |
| WHILE      | 12    | 'while' keyword |
| FOR        | 13    | 'for' keyword |
| DO         | 14    | 'do' keyword |
| BREAK      | 15    | 'break' keyword |
| CONTINUE   | 16    | 'continue' keyword |
| RETURN     | 17    | 'return' keyword |
| READ       | 18    | 'read' keyword |
| WRITE      | 19    | 'write' keyword |
| PLUS       | 20    | '+' operator |
| MINUS      | 21    | '-' operator |
| MULTIPLY   | 22    | '*' operator |
| DIVIDE     | 23    | '/' operator |
| MODULO     | 24    | '%' operator |
| EXPONENT   | 25    | '^' operator |
| BITWISE_AND| 26    | '&' operator |
| BITWISE_OR | 27    | '|' operator |
| BITWISE_XOR| 28    | '^' operator |
| BITWISE_NOT| 29    | '~' operator |
| LOGICAL_AND| 30    | '&&' operator |
| LOGICAL_OR | 31    | '||' operator |
| LESS       | 32    | '<' operator |
| LESS_EQUAL | 33    | '<=' operator |
| GREATER    | 34    | '>' operator |
| GREATER_EQUAL | 35 | '>=' operator |
| NOT_EQUAL  | 36    | '!=' operator |
| EQUAL_EQUAL| 37    | '==' operator |
| ASSIGN     | 38    | '=' operator |
| LEFT_PAREN | 39    | '(' character |
| RIGHT_PAREN| 40    | ')' character |
| LEFT_BRACE | 41    | '{' character |
| RIGHT_BRACE| 42    | '}' character |
| LEFT_BRACKET | 43  | '[' character |
| RIGHT_BRACKET | 44 | ']' character |
| COMMA      | 45    | ',' character |
| SEMICOLON  | 46    | ';' character |
| COLON      | 47    | ':' character |
| DOT        | 48    | '.' character |
| END_OF_FILE| 0     | End of input marker |

## Features

- Supports C-style comments (`//` and `/* */`)
- Modern cpp practice
- Recognizes character literals (`'a'`, `'\n'`) and string literals (`"hello"`)
- Handles all standard operators and keywords

## Usage (Ubuntu 24.04LTS)
To compile the lexical analyzer
```
g++ -o lexer lexical_analyzer.cpp
```
To run the analyzer on a source file
```
./lexer input_file.c
```
**Output format**
- For keywords, operators, and so on: `( token_id , - )`
- For identifiers and constants: `( token_id , lexeme )`

## Results on [Sample Code](sample_code)
Please refer to [Results_manual](results_manual.txt)

## Lex Version
With same functionality, refer to [lex_cplusplus](https://github.com/RZ-01/lex_cplusplus/tree/master)
