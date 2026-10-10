#include <stdio.h>
#include <ctype.h>

char prod[20][20], first[26][20], follow[26][20];
int n, fc[26], flc[26];

int add(char *set, int *cnt, char ch)
{
    for (int i = 0; i < *cnt; i++)
        if (set[i] == ch)
            return 0;
    set[(*cnt)++] = ch;
    return 1;
}

int findFirst(char *str, char *result)
{
    int cnt = 0, eps = 1;
    for (int i = 0; str[i]; i++)
    {
        char ch = str[i];
        if (!isupper(ch))
        {
            eps = (ch == '#');
            if (!eps)
                add(result, &cnt, ch);
            break;
        }
        int pos = ch - 'A', hasEps = 0;
        for (int j = 0; j < fc[pos]; j++)
            if (first[pos][j] == '#')
                hasEps = 1;
            else
                add(result, &cnt, first[pos][j]);
        if (!hasEps)
        {
            eps = 0;
            break;
        }
    }
    if (eps)
        add(result, &cnt, '#');
    return cnt;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    int change;
    do
    {
        change = 0;
        for (int i = 0; i < n; i++)
        {
            int left = prod[i][0] - 'A';
            char res[20];
            int cnt = findFirst(prod[i] + 2, res);
            for (int j = 0; j < cnt; j++)
                if (add(first[left], &fc[left], res[j]))
                    change = 1;
        }
    } while (change);

    add(follow[prod[0][0] - 'A'], &flc[prod[0][0] - 'A'], '$');
    do
    {
        change = 0;
        for (int i = 0; i < n; i++)
        {
            int left = prod[i][0] - 'A';
            for (int j = 2; prod[i][j]; j++)
            {
                if (!isupper(prod[i][j]))
                    continue;
                int cur = prod[i][j] - 'A';
                char res[20];
                int cnt = findFirst(prod[i] + j + 1, res);
                int eps = 0;
                for (int k = 0; k < cnt; k++)
                    if (res[k] == '#')
                        eps = 1;
                    else if (add(follow[cur], &flc[cur], res[k]))
                        change = 1;
                if (!prod[i][j + 1] || eps)
                    for (int k = 0; k < flc[left]; k++)
                        if (add(follow[cur], &flc[cur], follow[left][k]))
                            change = 1;
            }
        }
    } while (change);

    // ---- print ----
    printf("\nFIRST\n");
    for (int i = 0; i < 26; i++)
        if (fc[i])
        {
            printf("%c = { ", i + 'A');
            for (int j = 0; j < fc[i]; j++)
                printf("%c ", first[i][j]);
            printf("}\n");
        }
    printf("\nFOLLOW\n");
    for (int i = 0; i < 26; i++)
        if (flc[i])
        {
            printf("%c = { ", i + 'A');
            for (int j = 0; j < flc[i]; j++)
                printf("%c ", follow[i][j]);
            printf("}\n");
        }
    return 0;
}