// Name : Shridhar Kachare

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdint.h>

#define N 5

sem_t chopstick[N];
sem_t table;

/* Philosopher Function */
void *dphilo(void *arg)
{
    int pno = (int)(intptr_t)arg;

    int left = pno;
    int right = (pno + 1) % N;

    printf("\nPhilosopher %d is Thinking", pno + 1);
    sleep(1);

    printf("\nPhilosopher %d is Hungry", pno + 1);
    sleep(1);

    sem_wait(&table);

    sem_wait(&chopstick[left]);
    printf("\nPhilosopher %d picked Fork %d (Left)",
           pno + 1, left + 1);

    sem_wait(&chopstick[right]);
    printf("\nPhilosopher %d picked Fork %d (Right)",
           pno + 1, right + 1);

    printf("\nPhilosopher %d is now Eating", pno + 1);
    sleep(1);

    sem_post(&chopstick[right]);
    sem_post(&chopstick[left]);

    sem_post(&table);

    printf("\nPhilosopher %d has finished Eating", pno + 1);

    return NULL;
}

int main(void)
{
    pthread_t philo[N];
    int i;

    /* Initialize Forks */
    for (i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    /* Initialize Table */
    sem_init(&table, 0, 1);

    /* Create Philosopher Threads */
    for (i = 0; i < N; i++)
    {
        pthread_create(&philo[i],
                       NULL,
                       dphilo,
                       (void *)(intptr_t)i);
    }

    /* Wait for Threads */
    for (i = 0; i < N; i++)
    {
        pthread_join(philo[i], NULL);
    }

    /* Destroy Semaphores */
    for (i = 0; i < N; i++)
    {
        sem_destroy(&chopstick[i]);
    }

    sem_destroy(&table);

    printf("\n\nAll philosophers have finished eating.\n");

    return 0;
}