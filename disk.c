// Name : Shridhar Kachare

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[20], n, head, initial;
    int i, j, temp;
    int total, pos, size;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter disk requests:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    initial = head;

    printf("Enter disk size: ");
    scanf("%d", &size);

    /* ================= SSTF ================= */

    int visited[20] = {0};

    total = 0;

    printf("\nSSTF Order: ");

    for (i = 0; i < n; i++)
    {
        int min = 9999;
        int index = -1;

        for (j = 0; j < n; j++)
        {
            if (!visited[j] && abs(head - a[j]) < min)
            {
                min = abs(head - a[j]);
                index = j;
            }
        }

        visited[index] = 1;

        total += abs(head - a[index]);
        head = a[index];

        printf("%d ", head);
    }

    printf("\nSSTF Total Head Movement = %d\n", total);

    /* Sort Requests for SCAN and C-LOOK */

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    /* ================= SCAN ================= */

    head = initial;
    total = 0;
    pos = 0;

    while (pos < n && a[pos] < head)
    {
        pos++;
    }

    printf("\nSCAN Order: ");

    for (i = pos; i < n; i++)
    {
        total += abs(head - a[i]);
        head = a[i];

        printf("%d ", head);
    }

    total += abs(head - (size - 1));
    head = size - 1;

    for (i = pos - 1; i >= 0; i--)
    {
        total += abs(head - a[i]);
        head = a[i];

        printf("%d ", head);
    }

    printf("\nSCAN Total Head Movement = %d\n", total);

    /* ================= C-LOOK ================= */

    head = initial;
    total = 0;
    pos = 0;

    while (pos < n && a[pos] < head)
    {
        pos++;
    }

    printf("\nC-LOOK Order: ");

    for (i = pos; i < n; i++)
    {
        total += abs(head - a[i]);
        head = a[i];

        printf("%d ", head);
    }

    if (pos > 0)
    {
        total += abs(head - a[0]);
        head = a[0];

        printf("%d ", head);

        for (i = 1; i < pos; i++)
        {
            total += abs(head - a[i]);
            head = a[i];

            printf("%d ", head);
        }
    }

    printf("\nC-LOOK Total Head Movement = %d\n", total);

    return 0;
}
