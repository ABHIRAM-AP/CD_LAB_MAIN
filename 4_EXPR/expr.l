%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+(\.[0-9]+)?       { yylval = atof(yytext); return NUMBER; }

[ \t\r]+                { /* Ignore spaces, tabs, and carriage returns */ }

\n                      { return '\n'; } /* Return newline to YACC */

.                       { return yytext[0]; } /* Handles +, -, *, /, (, ) and any other char */

%%

int yywrap()
{
    return 1;
}