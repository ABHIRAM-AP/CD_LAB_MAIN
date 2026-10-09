
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int temp = 1;

int prec(char c)
{
    return (c == '*' || c == '/') ? 2 : (c == '+' || c == '-') ? 1
                                                               : 0;
}

void generate(char *exp)
{
    char op[50], val[50][20], t[20];
    int ot = -1, vt = -1, i;

    for (i = 0; exp[i]; i++)
    {
        char c = exp[i];

        if (isalnum((unsigned char)c))
        {
            val[++vt][0] = c;
            val[vt][1] = '\0';
        }
        else if (c == '(')
            op[++ot] = c;
        else if (c == ')')
        {
            while (ot >= 0 && op[ot] != '(')
            {
                sprintf(t, "t%d", temp++);
                printf("%s = %s %c %s\n",
                       t, val[vt - 1], op[ot--], val[vt]);
                strcpy(val[--vt], t);
            }
            if (ot >= 0)
                ot--;
        }
        else
        {
            while (ot >= 0 && op[ot] != '(' &&
                   prec(op[ot]) >= prec(c))
            {
                sprintf(t, "t%d", temp++);
                printf("%s = %s %c %s\n",
                       t, val[vt - 1], op[ot--], val[vt]);
                strcpy(val[--vt], t);
            }
            op[++ot] = c;
        }
    }

    while (ot >= 0)
    {
        sprintf(t, "t%d", temp++);
        printf("%s = %s %c %s\n",
               t, val[vt - 1], op[ot--], val[vt]);
        strcpy(val[--vt], t);
    }

    if (vt >= 0)
        printf("Result = %s\n", val[vt]);
}

int main()
{
    char exp[50];
    printf("Enter expression: ");
    scanf("%49s", exp);
    printf("\nIntermediate Code:\n");
    generate(exp);
    return 0;
}
