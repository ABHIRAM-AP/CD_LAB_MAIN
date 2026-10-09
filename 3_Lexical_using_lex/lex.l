%{
#include <stdio.h>
%}

digit   [0-9]
letter  [a-zA-Z_]
id      {letter}({letter}|{digit})*

%%

"#include"                 { printf("%s is a preprocessor directive\n", yytext); }

"<"[a-zA-Z0-9_.]+">"       { printf("%s is a header file\n", yytext); }

if|else|while|for|switch|case|break|continue|return|int|char|float|double|void|printf|scanf        { printf("%s is a keyword\n", yytext); }

"=="|"<="|">="|"!="        { printf("%s is a relational operator\n", yytext); }

"="                        { printf("%s is an assignment operator\n", yytext); }

"<"|">"                    { printf("%s is a relational operator\n", yytext); }

"++"|"--"                  { printf("%s is an increment/decrement operator\n", yytext); }

"+"|"-"|"*"|"/"|"%"    { printf("%s is an arithmetic operator\n", yytext); }

"&&"|"||"|"!"            { printf("%s is a logical operator\n", yytext); }

";"|","|"("|")"|"{"|"}"|"["|"]"   { printf("%s is a special symbol\n", yytext); }

\"[^\"]*\"                             { printf("%s is a string literal\n", yytext); }

[0-9]+(\.[0-9]+)?        { printf("%s is a number\n", yytext); }

{id}                       { printf("%s is an identifier\n", yytext); }

\/\/.*                     { printf("Single-line comment\n"); }

"/*"(.|\n)*"*/"      {    printf("Multi-line comment\n");}

[ \t\n]+                   ;

.                          { printf("%s is an unknown character\n", yytext); }

%%

int yywrap()
{
    return 1;
}

int main()
{
    yyin = fopen("input.txt","r");

    if(yyin == NULL)
    {
        printf("Cannot open input file\n");
        return 1;
    }

    yylex();

    fclose(yyin);

    return 0;
}