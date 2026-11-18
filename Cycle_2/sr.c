#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

char lhs[MAX], rhs[MAX][MAX], in[MAX], start, sStack[MAX][MAX], sAct[MAX][MAX], st[MAX];

int n, np, sIp[MAX];

void record(int d, int top, int ip, char *act)
{
    memcpy(sStack[d], st, top);
    sStack[d][top] = '\0';
    sIp[d] = ip;
    strcpy(sAct[d], act);
}

int parse(int d, int top, int ip)
{
    if (d >= MAX)
        return 0;
    if (ip == n && top == 1 && st[0] == start)
    {
        printf("%-10s %-10s %s\n", "STACK", "INPUT", "ACTION");
        printf("%-10s %-10s %s\n", "$", in, "-");
        for (int i = 0; i < d; i++)
            printf("%-10s %-10s %s\n", sStack[i], in + sIp[i], sAct[i]);
        return 1;
    }

    for (int p = 0; p < np; p++)
    {
        int len = strlen(rhs[p]);
        if (len == 0)
            continue;
        if (top >= len && strncmp(st + top - len, rhs[p], len) == 0)
        {
            char act[30];
            st[top - len] = lhs[p];
            snprintf(act, sizeof act, "REDUCE %c->%s", lhs[p], rhs[p]);
            record(d, top - len + 1, ip, act);
            if (parse(d + 1, top - len + 1, ip))
                return 1;
            memcpy(st + top - len, rhs[p], len);
        }
    }
    if (ip < n && top < MAX)
    {
        st[top] = in[ip];
        record(d, top + 1, ip + 1, "SHIFT");
        if (parse(d + 1, top + 1, ip + 1))
            return 1;
    }
    return 0;
}

int main()
{
    char line[MAX];
    printf("Enter total productions:");
    scanf("%d", &np);
    printf("Enter productions:");
    for (int i = 0; i < np; i++)
    {
        scanf("%s", line);
        lhs[i] = line[0];
        strcpy(rhs[i], line + 3);
    }
    start = lhs[0];
    printf("Input string:");
    scanf("%s", in);
    n = strlen(in);
    if (!parse(0, 0, 0))
        printf("STRING REJCTED");
    else
        printf("STRING ACCEPTED");
    return 0;
}