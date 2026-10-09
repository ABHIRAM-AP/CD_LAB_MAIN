#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0;

void S()
{
    if (input[pos] == '0' || input[pos] == '1')
        pos++;
    else
    {
        printf("Invalid\n");
        exit(0);
    }
    if (input[pos] == '0' || input[pos] == '1')
        S();
}

int main()
{
    printf("Enter input\n");
    scanf("%s", input);
    S();
    if (input[pos] == '\0')
        printf("Valid");
    else
        printf("invalid");
}