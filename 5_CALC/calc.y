
%{
    #include<stdio.h>
    #include<stdlib.h>

    void yyerror(char *s);
    int yylex();
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%left '(' ')'
%right UMINUS

%start input

%%

input: expr '\n' {
                    printf("Result: %d\n", $1);
                    return 0;
                  };

expr: expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr {
                        if ($3 == 0) {
                            yyerror("Division by zero");
                            $$ = 0;
                        }
                        else {
                            $$ = $1 / $3;
                        }
                    }
    | '(' expr ')' { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '+' expr %prec UMINUS { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;

%%

void yyerror(char *s)
{
    printf("Invalid expression: %s\n", s);
}

int main()
{
    printf("Enter an expression: ");
    yyparse();
    return 0;
}
