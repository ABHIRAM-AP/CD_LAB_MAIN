%{
#include<stdio.h>    
%}


%%
[0-9]+  { int n=atoi(yytext);
        if(n%2==0)printf("EVEN");
        else printf("ODD");
}
\n ;
. {printf("INVALID");}
%%

int yywrap(){return 1;}

int main()
{
    yylex();
}