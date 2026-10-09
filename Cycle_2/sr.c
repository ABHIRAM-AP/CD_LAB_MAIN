#include <stdio.h>
#include <string.h>

#define MAXP 30
#define MAXD 100

char lhs[MAXP], rhs[MAXP][20];
int np, n;
char in[64], st[MAXD + 5], start;

char sStack[MAXD][MAXD + 5], sAct[MAXD][40];
int sIp[MAXD];

void record(int d, int top, int ip, const char *act)
{
    memcpy(sStack[d], st, top);
    sStack[d][top] = '\0';
    sIp[d] = ip;
    strcpy(sAct[d], act);
}

int parse(int top, int ip, int d)
{
    if (d >= MAXD)
        return 0;
    if (ip == n && top == 1 && st[0] == start)
    {
        printf("%-15s %-15s %s\n", "STACK", "INPUT", "ACTION");
        printf("%-15s %-15s %s\n", "$", in, "-");
        for (int i = 0; i < d; i++)
            printf("%-15s %-15s %s\n", sStack[i], in + sIp[i], sAct[i]);
        return 1;
    }

    /* try every possible reduction */
    for (int p = 0; p < np; p++)
    {
        int len = strlen(rhs[p]);
        if (top >= len && strncmp(st + top - len, rhs[p], len) == 0)
        {
            char act[40];
            st[top - len] = lhs[p];
            snprintf(act, sizeof act, "REDUCE %c->%s", lhs[p], rhs[p]);
            record(d, top - len + 1, ip, act);
            if (parse(top - len + 1, ip, d + 1))
                return 1;
            memcpy(st + top - len, rhs[p], len); /* backtrack */
        }
    }

    /* try shift */
    if (ip < n && top < MAXD)
    {
        st[top] = in[ip];
        record(d, top + 1, ip + 1, "SHIFT");
        if (parse(top + 1, ip + 1, d + 1))
            return 1;
    }
    return 0;
}

int main()
{
    char line[40];
    printf("Number of productions: ");
    scanf("%d", &np);
    printf("Enter productions (e.g. E->E+E):\n");
    for (int i = 0; i < np; i++)
    {
        scanf("%39s", line);
        lhs[i] = line[0];
        strcpy(rhs[i], line + 3);
    }
    start = lhs[0];
    printf("Input string: ");
    scanf("%63s", in);
    n = strlen(in);

    if (!parse(0, 0, 0))
        printf("\nString REJECTED\n");
    else
        printf("\nString ACCEPTED\n");
    return 0;
}