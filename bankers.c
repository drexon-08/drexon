#include <stdio.h>

int main()
{
    int n, m;
    int alloc[10][10], max[10][10], avail[10];
    int need[10][10], work[10], finish[10] = {0};
    int safeSeq[10];

    int i, j, count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    if (n < 1 || n > 10 || m < 1 || m > 10)
    {
        printf("Invalid number of processes or resources.\n");
        return 1;
    }

    /* Input Allocation Matrix */
    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    /* Input Maximum Matrix */
    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    /* Input Available Resources */
    printf("\nEnter Available Resources:\n");
    for (j = 0; j < m; j++)
    {
        scanf("%d", &avail[j]);
        work[j] = avail[j];
    }

    /* Calculate Need Matrix */
    printf("\nNeed Matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];

            if (need[i][j] < 0)
            {
                printf("Invalid input: Allocation exceeds Maximum.\n");
                return 1;
            }

            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    /* Safety Algorithm */
    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int canExecute = 1;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canExecute = 0;
                        break;
                    }
                }

                if (canExecute)
                {
                    for (j = 0; j < m; j++)
                    {
                        work[j] += alloc[i][j];
                    }

                    safeSeq[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            break;
        }
    }

    /* Display Result */
    if (count == n)
    {
        printf("\nSystem is in SAFE STATE.\n");
        printf("Safe Sequence: ");

        for (i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);

            if (i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is in UNSAFE STATE.\n");
        printf("No safe sequence exists for the given state.\n");
    }

    return 0;
}