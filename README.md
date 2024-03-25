# Second Lab (SAVE_R)

This repository contains code for the second lab assignment. The `Save_R` functionality adds a table to the existing `table_type`.
[Original](https://github.com/Kharacternyk/univ-pr/)

### Used

- Flex 2.6.0
- Bison 3.8.2
- GCC 11.2.0

### Installation For Windows Users
Installation guide video by IQ95 The Homo Siliconiens: [Installation Guide Video](https://youtu.be/8hTqKad7aH8?si=b6y-DvoMklcHugxE)

### Compilation and Execution

1. Generate the parser: `bison -d parser.y`
2. Generate the lexer: `flex lexer.l`
3. Compile the code: 
    ```bash
    gcc lex.yy.c parser.tab.c main.c -o my_program -L"..your path here../flex-2.6.0/src/.libs" -lfl
    ```
To execute the program,  Linux / Cygwin Terminal :
Run the program with input file `1.txt`:
    ```bash
    ./my_program < 1.txt
    ```
