%{
#include<stdio.h>
int chars=0, words=0, lines=0;
int in=0;
%}

%%
\n       { lines++; chars++; in=1; }
[^ \t\n]+ { words++; chars+=yyleng; in=1; }
.        { chars++; in=1; }
%%

int yywrap()
{
    return 1;
}

int main()
{
    yylex();

    if(in)
        lines++;

    printf("\nLines=%d\nWords=%d\nCharacters=%d\n",
           lines, words, chars);

    return 0;
}