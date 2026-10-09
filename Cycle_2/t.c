#include <stdio.h>
#include <string.h>

char prod[20][30], stack[100], input[100];
int n, top, pos;

void show(FILE *out, char *action)
{
    stack[top + 1] = '\0';

    fprintf(out, "$%-15s ", stack);

    if (input[pos] == '\0')
        fprintf(out, "%-15s %s\n", "$", action);
    else
        fprintf(out, "%-15s %s\n", input + pos, action);
}

int reduce(FILE *out)
{
    int i, j, len;
    char action[50];

    for (i = 0; i < n; i++)
    {
        len = strlen(prod[i]) - 3;

        if (len <= top + 1)
        {
            j = top - len + 1;

            if (strncmp(&stack[j], prod[i] + 3, len) == 0)
            {
                top = j;
                stack[top] = prod[i][0];

                sprintf(action, "Reduce %s", prod[i]);
                show(out, action);

                return 1;
            }
        }
    }

    return 0;
}

void parse(FILE *out)
{
    int i = 0;

    top = -1;
    pos = 0;

    fprintf(out, "\n%-17s %-15s %s\n",
            "Stack", "Input", "Action");
    fprintf(out, "---------------------------------------------\n");

    while (input[i] != '\0')
    {
        stack[++top] = input[i++];
        pos = i;

        show(out, "Shift");

        while (reduce(out))
            ;
    }

    while (reduce(out))
        ;

    if (top == 0 && stack[0] == prod[0][0])
        show(out, "Accept");
    else
        show(out, "Reject");
}

int main()
{
    FILE *in, *out;
    int t, i;

    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    if (in == NULL || out == NULL)
    {
        printf("File opening error.\n");
        return 1;
    }

    fscanf(in, "%d", &n);

    for (i = 0; i < n; i++)
        fscanf(in, "%s", prod[i]);

    fscanf(in, "%d", &t);

    fprintf(out, "SHIFT REDUCE PARSER\n");
    fprintf(out, "===================\n");

    for (i = 1; i <= t; i++)
    {
        fscanf(in, "%s", input);

        fprintf(out, "\nTEST CASE %d\n", i);
        fprintf(out, "Input: %s\n", input);

        parse(out);
    }

    fclose(in);
    fclose(out);

    printf("Parsing completed.\n");
    printf("Results written to output.txt\n");

    return 0;
}