#include <stdio.h>
#include <string.h>

void acceptDFA(int states, int inputs, int delta[][inputs])
{
    for (int i = 0; i < states; i++)
    {
        printf("\n");
        for (int j = 0; j < inputs; j++)
        {
            printf("Transition(q%d,%d): q", i, j);
            scanf("%d", &delta[i][j]);
        }
    }
}

int findRep(int states, int currgrp, int group[])
{
    for (int i = 0; i < states; i++)
        if (group[i] == currgrp)
            return i;
    return -1;
}

int minimize(int states, int inputs, int delta[][inputs], int group[])
{
    int split, changed, count, temp[states], newgrp = 2;
    do
    {
        changed = 0;
        for (int currgrp = 0; currgrp < newgrp; currgrp++)
        {
            count = 0, split = 0;
            int rep = findRep(states, currgrp, group);
            if (rep == -1)
                continue;

            for (int i = rep + 1; i < states; i++)
            {
                if (group[i] != currgrp)
                    continue;
                for (int j = 0; j < inputs; j++)
                    if (group[delta[rep][j]] != group[delta[i][j]])
                    {
                        temp[count++] = i;
                        split = 1;
                        break;
                    }
            }
            for (int i = 0; i < count; i++)
                group[temp[i]] = newgrp;
            if (split)
            {
                newgrp++;
                changed = 1;
            }
        }
    } while (changed);
    return newgrp;
}

void displayGroup(int states, int currgrp, int group[])
{
    for (int i = 0; i < states; i++)
        if (currgrp == group[i])
            printf("q%d ", i);
}

void display(int totalgrp, int states, int inputs,
             int delta[states][inputs], int group[], int final[])
{
    printf("\nMinimized DFA Transition Table:\n");

    for (int i = 0; i < totalgrp; i++)
    {
        int rep = findRep(states, i, group);

        if (rep == -1)
            continue;

        int isFinal = 0;

        for (int k = 0; k < states; k++)
        {
            if (group[k] == i && final[k] == 1)
            {
                isFinal = 1;
                break;
            }
        }

        printf("\n State: %s[ ", isFinal ? "*" : "");

        displayGroup(states, i, group);

        printf("]\n");

        for (int j = 0; j < inputs; j++)
        {
            printf(" On input %d -> [ ", j);

            displayGroup(states, group[delta[rep][j]], group);

            printf("]\n");
        }
    }
}

void main()
{
    int states, inputs, temp, f, totalgrp;
    printf("Enter the no:of states & inputs:");
    scanf("%d %d", &states, &inputs);

    int delta[states][inputs], group[states], final[states];
    acceptDFA(states, inputs, delta);

    printf("\nEnter no: of final states: ");
    scanf("%d", &f);
    memset(group, 0, sizeof(group));
    memset(final, 0, sizeof final);
    printf("Enter final states: ");
    for (int i = 0; i < f; i++)
    {
        scanf("%d", &temp);
        group[temp] = 1;
        final[temp] = 1;
    }

    totalgrp = minimize(states, inputs, delta, group);
    display(totalgrp, states, inputs, group, delta, final);
}