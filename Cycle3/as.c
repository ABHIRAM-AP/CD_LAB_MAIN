#include <stdio.h>
#include <string.h>

#define MAX 500

void initialize()
{
    printf("\n8086 Assembly Code:\n");
    printf("MOV AX,@DATA\n");
    printf("MOV DS,AX\n\n");
}

void generateCode(char s[])
{
    char lhs[20], op1[20], op2[20];
    char op, rel[3], label[20];

    if (sscanf(s, "if %19s %2s %19s goto %19s",
               op1, rel, op2, label) == 4)
    {
        printf("MOV AX,%s\n", op1);
        printf("CMP AX,%s\n", op2);

        if (strcmp(rel, "<") == 0)
            printf("JL %s\n", label);
        else if (strcmp(rel, ">") == 0)
            printf("JG %s\n", label);
        else if (strcmp(rel, "<=") == 0)
            printf("JLE %s\n", label);
        else if (strcmp(rel, ">=") == 0)
            printf("JGE %s\n", label);
        else if (strcmp(rel, "==") == 0)
            printf("JE %s\n", label);
        else if (strcmp(rel, "!=") == 0)
            printf("JNE %s\n", label);

        printf("\n");
    }

    else if (sscanf(s, "goto %19s", label) == 1)
    {
        printf("JMP %s\n\n", label);
    }

    else if (s[strlen(s) - 1] == ':')
    {
        s[strlen(s) - 1] = '\0';
        printf("%s:\n", s);
    }

    else if (sscanf(s, "%19[^=]=%19[^+*/-]%c%19s",
                    lhs, op1, &op, op2) == 4)
    {
        printf("MOV AX,%s\n", op1);

        if (op == '+')
            printf("ADD AX,%s\n", op2);

        else if (op == '-')
            printf("SUB AX,%s\n", op2);

        else if (op == '*')
        {
            printf("MOV BX,%s\n", op2);
            printf("MUL BX\n");
        }

        else if (op == '/')
        {
            printf("MOV BX,%s\n", op2);
            printf("MOV DX,0\n");
            printf("DIV BX\n");
        }

        printf("MOV %s,AX\n\n", lhs);
    }

    else if (sscanf(s, "%19[^=]=%19s", lhs, op1) == 2)
    {
        printf("MOV AX,%s\n", op1);
        printf("MOV %s,AX\n\n", lhs);
    }
}

void terminate()
{
    printf("MOV AH,4CH\n");
    printf("INT 21H\n");
    printf("END\n");
}

int main()
{
    int n;
    char input[MAX];
    char *statement;

    printf("Enter number of TAC statements: ");
    scanf("%d", &n);

    printf("Enter all TAC statements in one line:\n");
    scanf(" %[^\n]", input);

    initialize();

    statement = strtok(input, ";");

    for (int i = 0; i < n && statement != NULL; i++)
    {
        generateCode(statement);
        statement = strtok(NULL, ";");
    }

    terminate();

    return 0;
}