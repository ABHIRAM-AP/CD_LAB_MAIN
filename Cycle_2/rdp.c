#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char input[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error()
{
    printf("Invalid Expression\n");
    exit(0);
}

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if (input[pos] == '+' || input[pos] == '-')
    {
        pos++;
        T();
        Eprime();
    }
}

void T()
{
    F();
    Tprime();
}

void Tprime()
{
    if (input[pos] == '*' || input[pos] == '/')
    {
        pos++;
        F();
        Tprime();
    }
}

void F()
{
    if (isalnum(input[pos]))
        pos++;
    else if (input[pos] == '(')
    {
        pos++;
        E();

        if (input[pos] == ')')
            pos++;
        else
            error();
    }
    else
        error();
}

int main()
{
    printf("Enter an arithmetic expression: ");
    scanf("%s", input);

    E();

    if (input[pos] == '\0')
        printf("Valid Expression\n");
    else
        error();

    return 0;
}