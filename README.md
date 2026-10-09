How to Run Flex Files
Commands
lex filename.l
gcc lex.yy.c
./a.out

Explanation
lex filename.l – Generates the C source file lex.yy.c.
gcc lex.yy.c – Compiles the generated C file.
./a.out – Executes the program.
Note
Replace filename.l with your Flex file name.
If lex is unavailable, use flex filename.l.
If you get a yywrap error, try gcc lex.yy.c -lfl.