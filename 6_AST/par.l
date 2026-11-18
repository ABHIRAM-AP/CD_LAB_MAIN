%{
    #include "y.tab.h"
    #include <stdlib.h>
%}

%%
[0-9]+       { yylval.val=atoi(yytext); return NUMBER; }
[a-zA-Z]     { yylval.var=yytext[0]; return ID; }
[ \t\r]+     ;
\n           { return '\n'; }
.            { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}