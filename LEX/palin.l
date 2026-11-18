%{
    #include<stdio.h>
    #include<string.h>    
%}

%%
[a-zA-Z]+ {
    int i,flag=1;
    int len=strlen(yytext);
    for(i=0;i<len/2;i++)
    {
        if(yytext[i]!=yytext[len-i-1]){
            flag=0;break;
        }
    }
    if(flag)printf("PALIN\n");
    else printf("NOT PALIN");
}


[^ \t\n] | \n | . ;

%%
int yywrap(){
    return 1;
}

int main()
{
    printf("Enter a string:");
    yylex();
}