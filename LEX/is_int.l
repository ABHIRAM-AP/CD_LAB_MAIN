%{
#include<stdio.h>    
%}



%%
[0-9]+\.[0-9]*  {printf("FLOAT: %s\n",yytext);}
[0-9]+  {printf("INTEGER: %s\n",yytext);}

.|\n ;
%%


int yywrap(){
    return 1;
}

int main()
{
    printf("Enter a number:");
    yylex();
}