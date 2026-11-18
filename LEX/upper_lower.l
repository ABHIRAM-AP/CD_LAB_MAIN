%{
    #include<stdio.h>
    int upper=0,lower=0;    
%}


%%
[a-z] {lower++;}
[A-Z] {upper++;}

. ;

%%

int yywrap(){return 1;}

int main()
{
    printf("Enter a text:");
    yylex();
    printf("Upper = %d\n",upper);
    printf("Lower= %d\n",lower);
}