%{
    #include<stdio.h>
    #include<stdlib.h>
    void yyerror(const char *s);
    int yylex(void);    
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input:expr '\n' {printf("Valid expression\n");}
    ;
expr
    : expr '+' expr
        { $$ = $1 + $3; }

    | expr '-' expr
        { $$ = $1 - $3; }

    | expr '*' expr
        { $$ = $1 * $3; }

    | expr '/' expr
        { $$ = $1 / $3; }

    | NUMBER
        { $$ = $1; }
    ;
%%

void yyerror(const char *s){
    printf("Invalid expression\n");
}

int main()
{
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}