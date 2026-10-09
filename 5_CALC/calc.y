%{
#include<stdio.h>
#include<stdlib.h>    

void yyerror(char *s);
int yylex(void);
%}

%token NUM
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%
program:
    program expr '\n' {printf("Result: %d\n", $2);}
    |
    ;

expr:
    NUM { $$= $1;}
    | expr '+' expr {$$=$1+$3;}
    | expr '-' expr {$$=$1 - $3;}
    | expr '*' expr {$$=$1 * $3;}
    | expr '/' expr {
        if ($3==0){
            yyerror("Division by zero");
            $$=0;
        }else{
            $$=$1 / $3;
        }
    }
    | '(' expr ')' {$$=$2;}
    ;
%%


void yyerror(char *s){
    fprintf(stderr,"Error: %s\n",s);
}

int main(void){
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}