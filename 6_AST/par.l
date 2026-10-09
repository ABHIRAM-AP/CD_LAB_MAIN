%{
#include "y.tab.h"
%}

%%

[0-9]+      { yylval.val = atoi(yytext); return NUMBER; }
[-+*/\n()]  { return yytext[0]; }
[ \t]       ; /* Skip spaces and tabs */
.           ;

%%

int yywrap() {
    return 1;
}