-- Count positive and negative numbers

%{
    #include<stdio.h>
    int pos=0,neg=0,zero=0;    
%}


%%
-[0-9]+ {neg++;}
[0-9]+ {
    int n=atoi(yytext);
    if(n>0)pos++;
    else zero++;
}

.|\n ;
%%

int yywrap()
{
    return 1;
}


int main()
{
    printf("Enter numbers:");
    yylex();
    printf("Positive=%d\n",pos);
    printf("Negative=%d\n",neg);
    printf("Zero=%d\n",zero);
}