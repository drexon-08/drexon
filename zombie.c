// Name : Shridhar Kachare

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Bubble Sort */
void bubbleSort(int arr[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/* Display Array */
void display(int arr[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main()
{
    int arr[100];
    int n, i;
    pid_t pid;

    printf("====================================\n");
    printf("      FORK AND WAIT PROGRAM\n");
    printf("====================================\n");

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    pid = fork();

    if (pid < 0)
    {
        printf("Fork Failed!\n");
        return 1;
    }

    /* Child Process */
    if (pid == 0)
    {
        printf("\n========================\n");
        printf("   CHILD PROCESS\n");
        printf("========================\n");

        printf("Child PID : %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        bubbleSort(arr, n);

        printf("Sorted Array (Bubble Sort): ");
        display(arr, n);

        printf("Child Process Completed.\n");
        exit(0);
    }

    /* Parent Process */
    else
    {
        wait(NULL);

        printf("\n========================\n");
        printf("   PARENT PROCESS\n");
        printf("========================\n");

        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        printf("Child has finished execution.\n");
    }

    return 0;
}