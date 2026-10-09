
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STMT 20
#define MAX_LEN 20

struct Statement
{
    char lhs[MAX_LEN], op1[MAX_LEN], op2[MAX_LEN], op;
};

int isNumber(char *s)
{
    if (*s == '\0')
        return 0;

    for (int i = 0; s[i]; i++)
        if (!isdigit((unsigned char)s[i]))
            return 0;

    return 1;
}

void readStatements(struct Statement s[], int n)
{
    for (int i = 0; i < n; i++)
    {
        char str[50];

        scanf("%49s", str);
        sscanf(str, "%19[^=]=%19s", s[i].lhs, s[i].op1);

        char *p = strpbrk(s[i].op1, "+-*/");

        if (p)
        {
            s[i].op = *p;
            *p = '\0';
            strcpy(s[i].op2, p + 1);
        }
        else
        {
            s[i].op = '\0';
            s[i].op2[0] = '\0';
        }
    }
}

void constantPropagation(struct Statement s[], int n)
{
    char value[MAX_STMT][MAX_LEN] = {{0}};
    int known[MAX_STMT] = {0};

    printf("\nAfter Constant Propagation:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (known[j] && strcmp(s[i].op1, s[j].lhs) == 0)
                strcpy(s[i].op1, value[j]);

            if (known[j] && strcmp(s[i].op2, s[j].lhs) == 0)
                strcpy(s[i].op2, value[j]);
        }

        if (s[i].op == '\0' && isNumber(s[i].op1))
        {
            known[i] = 1;
            strcpy(value[i], s[i].op1);
        }

        printf("%s = %s", s[i].lhs, s[i].op1);

        if (s[i].op != '\0')
            printf(" %c %s", s[i].op, s[i].op2);

        printf("\n");
    }
}

int main()
{
    struct Statement s[MAX_STMT];
    int n;

    printf("Enter number of statements: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_STMT)
    {
        printf("Invalid number of statements.\n");
        return 1;
    }

    printf("Enter statements (a=5, b=a, c=a+b):\n");

    readStatements(s, n);
    constantPropagation(s, n);

    return 0;
}
