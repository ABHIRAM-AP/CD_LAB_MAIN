#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][20], first[26][20], follow[26][20];
int n, firstCnt[26], followCnt[26];

int add(char set[], int *cnt, char ch)
{
    for (int i = 0; i < *cnt; i++)
        if (set[i] == ch)
            return 0;

    set[(*cnt)++] = ch;
    return 1;
}

int findFirst(char str[], char result[])
{
    int cnt = 0, epsilon = 1;

    for (int i = 0; str[i]; i++)
    {
        char ch = str[i];

        if (!isupper(ch))
        {
            if (ch != '#')
                add(result, &cnt, ch);
            break;
        }

        int pos = ch - 'A', hasEps = 0;

        for (int j = 0; j < firstCnt[pos]; j++)
            if (first[pos][j] == '#')
                hasEps = 1;
            else
                add(result, &cnt, first[pos][j]);

        if (!hasEps)
        {
            epsilon = 0;
            break;
        }
    }

    if (epsilon)
        add(result, &cnt, '#');

    return cnt;
}

void findFollow()
{
    int start = prod[0][0] - 'A';
    add(follow[start], &followCnt[start], '$');

    int change;

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
                char result[20];
                int cnt = findFirst(prod[i] + j + 1, result);
                int epsilon = 0;

                for (int k = 0; k < cnt; k++)
                    if (result[k] == '#')
                        epsilon = 1;
                    else if (add(follow[cur],
                                 &followCnt[cur], result[k]))
                        change = 1;

                if (!prod[i][j + 1] || epsilon)
                    for (int k = 0; k < followCnt[left]; k++)
                        if (add(follow[cur],
                                &followCnt[cur], follow[left][k]))
                            change = 1;
            }
        }

    } while (change);
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    int change;

    /* FIRST */
    do
    {
        change = 0;

        for (int i = 0; i < n; i++)
        {
            int left = prod[i][0] - 'A';
            char result[20];
            int cnt = findFirst(prod[i] + 2, result);

            for (int j = 0; j < cnt; j++)
                if (add(first[left],
                        &firstCnt[left],
                        result[j]))
                    change = 1;
        }

    } while (change);

    /* FOLLOW */
    findFollow();

    printf("\nFIRST\n");

    for (int i = 0; i < 26; i++)
        if (firstCnt[i])
        {
            printf("%c = { ", i + 'A');

            for (int j = 0; j < firstCnt[i]; j++)
                printf("%c ", first[i][j]);

            printf("}\n");
        }

    printf("\nFOLLOW\n");

    for (int i = 0; i < 26; i++)
        if (followCnt[i])
        {
            printf("%c = { ", i + 'A');

            for (int j = 0; j < followCnt[i]; j++)
                printf("%c ", follow[i][j]);

            printf("}\n");
        }

    return 0;
}
