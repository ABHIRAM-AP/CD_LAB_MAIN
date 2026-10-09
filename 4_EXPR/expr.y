%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%right UMINUS

%start input

%%

input
    : expr '\n'  /* Added '\n' to match the Enter key */
      {
          printf("Valid arithmetic expression\n");
          return 0; /* Stop parsing successfully */
      }
    ;

expr
    : expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | '-' expr %prec UMINUS
    | '+' expr %prec UMINUS
    | NUMBER
    ;

%%

void yyerror(const char *s)
{
    printf("Invalid arithmetic expression\n");
}

int main()
{
    printf("Enter an expression: ");
    yyparse();
    return 0;
}