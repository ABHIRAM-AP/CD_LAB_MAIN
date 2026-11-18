%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+(\.[0-9]+)?       { yylval = atof(yytext); return NUMBER; }

[ \t\r]+                ;

\n                      { return '\n'; }

.                       { return yytext[0]; } 
%%

int yywrap()
{
    return 1;
}