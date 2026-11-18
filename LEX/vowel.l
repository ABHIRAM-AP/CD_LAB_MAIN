%{
    #include<stdio.h>
    int vowels=0,consonants=0;    
%}


%%
[aeiouAEIOU]    {vowels++;}
[a-zA-Z]    {consonants++;}
.|\n    ;
%%
int yywrap(){
    return 1;
}

int main()
{
    printf("Enter a string:\n");
    yylex();

    printf("Vowels= %d\n",vowels);
    printf("Consonants= %d\n",consonants);
}