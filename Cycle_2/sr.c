#include <stdio.h>
#include <string.h>

#define MAXP 10
#define MAXD 50

char lhs[MAXP], rhs[MAXP][10];
int np, n;
char in[20], st[MAXD], start;

char sStack[MAXD][MAXD], sAct[MAXD][30];
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
            continue; /* skip epsilon productions */
        if (top >= len && strncmp(st + top - len, rhs[p], len) == 0)
        {
            char act[30];
            st[top - len] = lhs[p];
            snprintf(act, sizeof act, "REDUCE %c->%s", lhs[p], rhs[p]);
            record(d, top - len + 1, ip, act);
            if (parse(top - len + 1, ip, d + 1))
                return 1;
            memcpy(st + top - len, rhs[p], len);
        }
    }

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
    char line[20];
    printf("Number of productions: ");
    scanf("%d", &np);
    printf("Enter productions (e.g. E->E+E):\n");
    for (int i = 0; i < np; i++)
    {
        scanf("%19s", line);
        lhs[i] = line[0];
        strcpy(rhs[i], line + 3);
    }
    start = lhs[0];
    printf("Input string: ");
    scanf("%19s", in);
    n = strlen(in);

    if (!parse(0, 0, 0))
        printf("\nString REJECTED\n");
    else
        printf("\nString ACCEPTED\n");
    return 0;
}